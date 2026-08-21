#include "trash_tool.h"

#include <cassert>
#include <chrono>
#include <iostream>
#include <map>
#include <vector>

using namespace work_disk::tools::lifecycle::trash_tool;

namespace {
class Store final : public TrashStore {
public:
    bool put(const TrashEntry& e) override { if (data.count(e.itemId)) return false; data[e.itemId] = e; return true; }
    bool find(const std::string& id, TrashEntry& e) const override { auto it=data.find(id); if(it==data.end()||claimed.count(id)) return false; e=it->second; return true; }
    std::vector<TrashEntry> list() const override { std::vector<TrashEntry> out; for(const auto& [id,e]:data) if(!claimed.count(id)) out.push_back(e); return out; }
    TrashClaimResult claimForRestore(const std::string& id, TrashEntry& e) override { return claim(id,e); }
    TrashClaimResult claimForDestruction(const std::string& id, TrashEntry& e) override { return claim(id,e); }
    bool completeRestore(const std::string& id) override { return complete(id); }
    bool completeDestruction(const std::string& id) override { return complete(id); }
    bool releaseClaim(const std::string& id) override { return claimed.erase(id)!=0; }
private:
    TrashClaimResult claim(const std::string& id, TrashEntry& e) { auto it=data.find(id); if(it==data.end()) return TrashClaimResult::NotFound; if(claimed.count(id)) return TrashClaimResult::Conflict; claimed.insert(id); e=it->second; return TrashClaimResult::Claimed; }
    bool complete(const std::string& id) { auto it=data.find(id); if(it==data.end()||!claimed.count(id)) return false; data.erase(it); claimed.erase(id); return true; }
    std::map<std::string,TrashEntry> data;
    std::map<std::string,bool> claimed;
};
class Policy final : public TrashRetentionPolicy { public: bool expiresAt(TrashTime t, TrashTime& out) const override { out=t+std::chrono::hours(24*90); return true; } };
class Restore final : public TrashRestoreBoundary { public: bool restore(const TrashEntry&) override { return true; } };
class Destroy final : public TrashDestructionBoundary { public: bool destroy(const TrashEntry&) override { ++calls; return succeed; } bool succeed=true; int calls=0; };
TrashEntryInput input(const char* id, TrashTime deleted) { return {id,"entry","E", "entries", "payload", deleted}; }
}

int main() {
    Store store; Policy policy; Restore restore; Destroy destroy;
    TrashTool tool(store, policy, restore, destroy);
    const auto now = std::chrono::system_clock::now();
    const TrashAuthority auth{"AUTH"};

    assert(tool.intake("I1", input("A", now)).succeeded());
    const auto noPurge = tool.purgeExpired("P1", auth, now);
    assert(noPurge.outcome() == TrashOutcome::NothingToPurge);
    assert(store.list().size() == 1);

    const auto purged = tool.purgeExpired("P2", auth, now + std::chrono::hours(24*91));
    assert(purged.outcome() == TrashOutcome::Purged);
    assert(store.list().empty());

    assert(tool.intake("I2", input("B", now)).succeeded());
    destroy.succeed = false;
    const auto failed = tool.purgeExpired("P3", auth, now + std::chrono::hours(24*91));
    assert(failed.outcome() == TrashOutcome::PartiallyEmptied);
    assert(store.list().size() == 1);

    std::cout << "BOT_05_TRASH_PURGE_TEST=PASS\n";
    return 0;
}
