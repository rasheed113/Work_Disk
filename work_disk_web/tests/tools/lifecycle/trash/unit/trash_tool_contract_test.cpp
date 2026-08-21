#include "trash_tool.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

using namespace work_disk::tools::lifecycle::trash_tool;

namespace {

class TestStore final : public TrashStore {
public:
    bool put(const TrashEntry& entry) override {
        if (entries_.count(entry.itemId) != 0) {
            return false;
        }
        entries_[entry.itemId] = entry;
        return true;
    }

    bool find(const std::string& itemId, TrashEntry& entry) const override {
        const auto it = entries_.find(itemId);
        if (it == entries_.end() || claimed_.count(itemId) != 0) {
            return false;
        }
        entry = it->second;
        return true;
    }

    std::vector<TrashEntry> list() const override {
        std::vector<TrashEntry> result;
        for (const auto& [id, entry] : entries_) {
            if (claimed_.count(id) == 0) {
                result.push_back(entry);
            }
        }
        return result;
    }

    TrashClaimResult claimForRestore(const std::string& itemId, TrashEntry& entry) override {
        return claim(itemId, entry);
    }

    TrashClaimResult claimForDestruction(const std::string& itemId, TrashEntry& entry) override {
        return claim(itemId, entry);
    }

    bool completeRestore(const std::string& itemId) override {
        const auto it = entries_.find(itemId);
        if (it == entries_.end() || claimed_.count(itemId) == 0) return false;
        entries_.erase(it);
        claimed_.erase(itemId);
        return true;
    }

    bool completeDestruction(const std::string& itemId) override {
        const auto it = entries_.find(itemId);
        if (it == entries_.end() || claimed_.count(itemId) == 0) return false;
        entries_.erase(it);
        claimed_.erase(itemId);
        return true;
    }

    bool releaseClaim(const std::string& itemId) override {
        return claimed_.erase(itemId) != 0;
    }

private:
    TrashClaimResult claim(const std::string& itemId, TrashEntry& entry) {
        const auto it = entries_.find(itemId);
        if (it == entries_.end()) return TrashClaimResult::NotFound;
        if (claimed_.count(itemId) != 0) return TrashClaimResult::Conflict;
        claimed_.insert(itemId);
        entry = it->second;
        return TrashClaimResult::Claimed;
    }

    std::map<std::string, TrashEntry> entries_;
    std::map<std::string, bool> claimed_;
};

class ThreeMonthPolicy final : public TrashRetentionPolicy {
public:
    bool expiresAt(TrashTime deletedAt, TrashTime& result) const override {
        result = deletedAt + std::chrono::hours(24 * 90);
        return true;
    }
};

class RestoreBoundary final : public TrashRestoreBoundary {
public:
    bool shouldSucceed = true;
    int calls = 0;
    bool restore(const TrashEntry&) override {
        ++calls;
        return shouldSucceed;
    }
};

class DestructionBoundary final : public TrashDestructionBoundary {
public:
    bool shouldSucceed = true;
    int calls = 0;
    bool destroy(const TrashEntry&) override {
        ++calls;
        return shouldSucceed;
    }
};

TrashEntryInput inputFor(const char* id, TrashTime deletedAt) {
    return TrashEntryInput{
        id,
        "fleet-entry",
        "ENTRY-001",
        "fleet/entries",
        "payload/ENTRY-001",
        deletedAt
    };
}

TrashAuthority authority() {
    return TrashAuthority{"AUTH-001"};
}

void test_intake_requires_preservation_reference() {
    TestStore store;
    ThreeMonthPolicy policy;
    RestoreBoundary restore;
    DestructionBoundary destruction;
    TrashTool tool(store, policy, restore, destruction);

    auto input = inputFor("TRASH-001", TrashTime{});
    input.payloadReference.clear();
    const auto result = tool.intake("OP-1", input);
    assert(result.outcome() == TrashOutcome::Failed);
    assert(result.error() == TrashError::InvalidRequest);
}

void test_restore_success() {
    TestStore store;
    ThreeMonthPolicy policy;
    RestoreBoundary restore;
    DestructionBoundary destruction;
    TrashTool tool(store, policy, restore, destruction);

    const auto deletedAt = std::chrono::system_clock::now();
    assert(tool.intake("OP-1", inputFor("TRASH-001", deletedAt)).succeeded());
    const auto result = tool.restore("OP-2", authority(), "TRASH-001", deletedAt + std::chrono::hours(1));
    assert(result.outcome() == TrashOutcome::Restored);
    assert(restore.calls == 1);
    assert(store.list().empty());
}

void test_restore_after_expiry_is_blocked() {
    TestStore store;
    ThreeMonthPolicy policy;
    RestoreBoundary restore;
    DestructionBoundary destruction;
    TrashTool tool(store, policy, restore, destruction);

    const auto deletedAt = std::chrono::system_clock::now();
    assert(tool.intake("OP-1", inputFor("TRASH-001", deletedAt)).succeeded());
    const auto result = tool.restore("OP-2", authority(), "TRASH-001", deletedAt + std::chrono::hours(24 * 91));
    assert(result.outcome() == TrashOutcome::Expired);
    assert(restore.calls == 0);
}

void test_delete_one_destroys_only_claimed_item() {
    TestStore store;
    ThreeMonthPolicy policy;
    RestoreBoundary restore;
    DestructionBoundary destruction;
    TrashTool tool(store, policy, restore, destruction);

    const auto now = std::chrono::system_clock::now();
    assert(tool.intake("OP-1", inputFor("TRASH-001", now)).succeeded());
    assert(tool.intake("OP-2", inputFor("TRASH-002", now)).succeeded());

    const auto result = tool.deleteOne("OP-3", authority(), "TRASH-001");
    assert(result.outcome() == TrashOutcome::Destroyed);
    assert(destruction.calls == 1);
    assert(store.list().size() == 1);
}

void test_failed_destruction_retains_item() {
    TestStore store;
    ThreeMonthPolicy policy;
    RestoreBoundary restore;
    DestructionBoundary destruction;
    destruction.shouldSucceed = false;
    TrashTool tool(store, policy, restore, destruction);

    const auto now = std::chrono::system_clock::now();
    assert(tool.intake("OP-1", inputFor("TRASH-001", now)).succeeded());
    const auto result = tool.deleteOne("OP-2", authority(), "TRASH-001");
    assert(result.outcome() == TrashOutcome::Failed);
    assert(result.error() == TrashError::DestructionFailure);
    assert(store.list().size() == 1);
}

void test_empty_trash_removes_all_successfully() {
    TestStore store;
    ThreeMonthPolicy policy;
    RestoreBoundary restore;
    DestructionBoundary destruction;
    TrashTool tool(store, policy, restore, destruction);

    const auto now = std::chrono::system_clock::now();
    assert(tool.intake("OP-1", inputFor("TRASH-001", now)).succeeded());
    assert(tool.intake("OP-2", inputFor("TRASH-002", now)).succeeded());
    const auto result = tool.empty("OP-3", authority());
    assert(result.outcome() == TrashOutcome::Emptied);
    assert(store.list().empty());
    assert(destruction.calls == 2);
}

void test_missing_authority_never_destroys() {
    TestStore store;
    ThreeMonthPolicy policy;
    RestoreBoundary restore;
    DestructionBoundary destruction;
    TrashTool tool(store, policy, restore, destruction);

    const auto now = std::chrono::system_clock::now();
    assert(tool.intake("OP-1", inputFor("TRASH-001", now)).succeeded());
    const auto result = tool.deleteOne("OP-2", TrashAuthority{}, "TRASH-001");
    assert(result.error() == TrashError::MissingAuthority);
    assert(destruction.calls == 0);
}

} // namespace

int main() {
    test_intake_requires_preservation_reference();
    test_restore_success();
    test_restore_after_expiry_is_blocked();
    test_delete_one_destroys_only_claimed_item();
    test_failed_destruction_retains_item();
    test_empty_trash_removes_all_successfully();
    test_missing_authority_never_destroys();

    std::cout << "BOT_05_TRASH_CONTRACT_TEST=PASS\n";
    return 0;
}
