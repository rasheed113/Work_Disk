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
    bool put(const TrashEntry& entry) override { if (entries_.count(entry.itemId)) return false; entries_[entry.itemId] = entry; return true; }
    bool find(const std::string& itemId, TrashEntry& entry) const override { const auto it=entries_.find(itemId); if(it==entries_.end()) return false; entry=it->second; return true; }
    std::vector<TrashEntry> list() const override { std::vector<TrashEntry> result; for(const auto& [id,entry]:entries_) result.push_back(entry); return result; }
    TrashClaimResult claimForRestore(const std::string& id, TrashTime now, TrashEntry& entry) override {
        const auto it=entries_.find(id); if(it==entries_.end()) return TrashClaimResult::NotFound; if(claimed_.count(id)) return TrashClaimResult::Conflict; if(now>=it->second.expiresAt) return TrashClaimResult::Expired; claimed_.insert(id); entry=it->second; return TrashClaimResult::Claimed;
    }
    TrashClaimResult claimForDestruction(const std::string& id, TrashEntry& entry) override { return claim(id,entry); }
    bool completeRestore(const std::string& id) override { return complete(id); }
    bool completeDestruction(const std::string& id) override { return complete(id); }
    bool releaseClaim(const std::string& id) override { return claimed_.erase(id)!=0; }
private:
    TrashClaimResult claim(const std::string& id, TrashEntry& entry) { const auto it=entries_.find(id); if(it==entries_.end()) return TrashClaimResult::NotFound; if(claimed_.count(id)) return TrashClaimResult::Conflict; claimed_.insert(id); entry=it->second; return TrashClaimResult::Claimed; }
    bool complete(const std::string& id) { const auto it=entries_.find(id); if(it==entries_.end()||!claimed_.count(id)) return false; entries_.erase(it); claimed_.erase(id); return true; }
    std::map<std::string,TrashEntry> entries_;
    std::map<std::string,bool> claimed_;
};
class ThreeMonthPolicy final : public TrashRetentionPolicy { public: bool expiresAt(TrashTime deletedAt, TrashTime& result) const override { result=deletedAt+std::chrono::hours(24*90); return true; } };
class RestoreBoundary final : public TrashRestoreBoundary { public: bool shouldSucceed=true; int calls=0; bool restore(const TrashEntry&) override { ++calls; return shouldSucceed; } };
class DestructionBoundary final : public TrashDestructionBoundary { public: bool shouldSucceed=true; int calls=0; bool destroy(const TrashEntry&) override { ++calls; return shouldSucceed; } };
TrashEntryInput inputFor(const char* id, TrashTime deletedAt) { return {id,"fleet-entry","ENTRY-001","fleet/entries","payload/ENTRY-001",deletedAt}; }
TrashAuthority authority() { return {"AUTH-001"}; }

void test_intake_requires_preservation_reference() { TestStore s; ThreeMonthPolicy p; RestoreBoundary r; DestructionBoundary d; TrashTool t(s,p,r,d); auto in=inputFor("TRASH-001",TrashTime{}); in.payloadReference.clear(); const auto x=t.intake("OP-1",in); assert(x.outcome()==TrashOutcome::Failed); assert(x.error()==TrashError::InvalidRequest); }
void test_restore_success() { TestStore s; ThreeMonthPolicy p; RestoreBoundary r; DestructionBoundary d; TrashTool t(s,p,r,d); const auto at=std::chrono::system_clock::now(); assert(t.intake("OP-1",inputFor("TRASH-001",at)).succeeded()); const auto x=t.restore("OP-2",authority(),"TRASH-001",at+std::chrono::hours(1)); assert(x.outcome()==TrashOutcome::Restored); assert(r.calls==1); assert(s.list().empty()); }
void test_restore_after_expiry_is_blocked() { TestStore s; ThreeMonthPolicy p; RestoreBoundary r; DestructionBoundary d; TrashTool t(s,p,r,d); const auto at=std::chrono::system_clock::now(); assert(t.intake("OP-1",inputFor("TRASH-001",at)).succeeded()); const auto x=t.restore("OP-2",authority(),"TRASH-001",at+std::chrono::hours(24*91)); assert(x.outcome()==TrashOutcome::Expired); assert(r.calls==0); }
void test_delete_one_destroys_only_claimed_item() { TestStore s; ThreeMonthPolicy p; RestoreBoundary r; DestructionBoundary d; TrashTool t(s,p,r,d); const auto now=std::chrono::system_clock::now(); assert(t.intake("OP-1",inputFor("TRASH-001",now)).succeeded()); assert(t.intake("OP-2",inputFor("TRASH-002",now)).succeeded()); const auto x=t.deleteOne("OP-3",authority(),"TRASH-001"); assert(x.outcome()==TrashOutcome::Destroyed); assert(d.calls==1); assert(s.list().size()==1); }
void test_failed_destruction_retains_item() { TestStore s; ThreeMonthPolicy p; RestoreBoundary r; DestructionBoundary d; d.shouldSucceed=false; TrashTool t(s,p,r,d); const auto now=std::chrono::system_clock::now(); assert(t.intake("OP-1",inputFor("TRASH-001",now)).succeeded()); const auto x=t.deleteOne("OP-2",authority(),"TRASH-001"); assert(x.outcome()==TrashOutcome::Failed); assert(x.error()==TrashError::DestructionFailure); assert(s.list().size()==1); }
void test_empty_trash_removes_all_successfully() { TestStore s; ThreeMonthPolicy p; RestoreBoundary r; DestructionBoundary d; TrashTool t(s,p,r,d); const auto now=std::chrono::system_clock::now(); assert(t.intake("OP-1",inputFor("TRASH-001",now)).succeeded()); assert(t.intake("OP-2",inputFor("TRASH-002",now)).succeeded()); const auto x=t.empty("OP-3",authority()); assert(x.outcome()==TrashOutcome::Emptied); assert(s.list().empty()); assert(d.calls==2); }
void test_missing_authority_never_destroys() { TestStore s; ThreeMonthPolicy p; RestoreBoundary r; DestructionBoundary d; TrashTool t(s,p,r,d); const auto now=std::chrono::system_clock::now(); assert(t.intake("OP-1",inputFor("TRASH-001",now)).succeeded()); const auto x=t.deleteOne("OP-2",TrashAuthority{},"TRASH-001"); assert(x.error()==TrashError::MissingAuthority); assert(d.calls==0); }
}

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
