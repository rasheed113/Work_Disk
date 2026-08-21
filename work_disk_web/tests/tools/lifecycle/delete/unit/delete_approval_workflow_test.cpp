#include "delete_tool.h"

#include <cassert>
#include <iostream>
#include <string>

using namespace work_disk::tools::lifecycle::delete_tool;

class FakeExecutionBoundary final : public DeleteExecutionBoundary {
public:
    int calls = 0;
    DeleteExecutionResult next = DeleteExecutionResult::deleted();

    DeleteExecutionResult execute(const DeleteRequest&) override {
        ++calls;
        return next;
    }
};

class FakeApprovalBoundary final : public DeleteApprovalBoundary {
public:
    int calls = 0;
    DeleteApprovalResult next = DeleteApprovalResult::pending();

    DeleteApprovalResult requestApproval(const DeleteRequest&) override {
        ++calls;
        return next;
    }
};

class FakePendingStore final : public DeletePendingOperationStore {
public:
    bool held = false;
    bool approved = false;
    int holdCalls = 0;
    int releaseCalls = 0;
    int completeCalls = 0;

    PendingOperationOutcome hold(const DeleteRequest&) override {
        ++holdCalls;
        if (held || approved) return PendingOperationOutcome::AlreadyHeld;
        held = true;
        return PendingOperationOutcome::Held;
    }

    PendingOperationOutcome markApproved(
        const std::string&, const std::string& evidence
    ) override {
        if (!held || evidence.empty()) return PendingOperationOutcome::Conflict;
        held = false;
        approved = true;
        return PendingOperationOutcome::Approved;
    }

    PendingOperationOutcome release(const std::string&) override {
        if (!held) return PendingOperationOutcome::Missing;
        held = false;
        ++releaseCalls;
        return PendingOperationOutcome::Released;
    }

    bool isHeld(const std::string&) const override { return held; }
    bool isApproved(const std::string&) const override { return approved; }

    PendingOperationOutcome complete(const std::string&) override {
        if (!approved) return PendingOperationOutcome::Conflict;
        approved = false;
        ++completeCalls;
        return PendingOperationOutcome::Completed;
    }
};

static DeleteRequest approvalRequest() {
    DeleteRequest request;
    request.requestId = "REQ-APPROVAL-001";
    request.targetType = "FleetEntry";
    request.targetId = "ENTRY-001";
    request.executionMode = DeleteExecutionMode::ApprovalRequired;
    request.authority.authorityReference = "AUTH-001";
    return request;
}

static void test_pending_does_not_delete() {
    FakeExecutionBoundary execution;
    FakeApprovalBoundary approval;
    FakePendingStore pending;

    DeleteTool tool(execution, pending, approval);
    const auto result = tool.execute(approvalRequest());

    assert(result.outcome() == DeleteOutcome::PendingApproval);
    assert(execution.calls == 0);
    assert(approval.calls == 1);
    assert(pending.held);
}

static void test_repeated_pending_request_does_not_duplicate_approval() {
    FakeExecutionBoundary execution;
    FakeApprovalBoundary approval;
    FakePendingStore pending;

    DeleteTool tool(execution, pending, approval);
    const auto request = approvalRequest();

    assert(tool.execute(request).outcome() == DeleteOutcome::PendingApproval);
    assert(tool.execute(request).outcome() == DeleteOutcome::PendingApproval);
    assert(approval.calls == 1);
    assert(pending.holdCalls == 2);
    assert(execution.calls == 0);
}

static void test_approval_commits_delete() {
    FakeExecutionBoundary execution;
    FakeApprovalBoundary approval;
    FakePendingStore pending;

    DeleteTool tool(execution, pending, approval);
    auto request = approvalRequest();

    assert(tool.execute(request).outcome() == DeleteOutcome::PendingApproval);

    request.approvalDecision = DeleteApprovalDecision::Approved;
    request.authority.approvalEvidence = "APPROVAL-EVIDENCE-001";

    const auto result = tool.execute(request);

    assert(result.outcome() == DeleteOutcome::Deleted);
    assert(result.succeeded());
    assert(execution.calls == 1);
    assert(pending.completeCalls == 1);
    assert(!pending.held);
}

static void test_rejection_releases_without_delete() {
    FakeExecutionBoundary execution;
    FakeApprovalBoundary approval;
    FakePendingStore pending;

    DeleteTool tool(execution, pending, approval);
    auto request = approvalRequest();

    assert(tool.execute(request).outcome() == DeleteOutcome::PendingApproval);

    request.approvalDecision = DeleteApprovalDecision::Rejected;
    request.authority.approvalEvidence = "REJECTION-EVIDENCE-001";

    const auto result = tool.execute(request);

    assert(result.outcome() == DeleteOutcome::Rejected);
    assert(!result.succeeded());
    assert(execution.calls == 0);
    assert(pending.releaseCalls == 1);
    assert(!pending.held);
}

static void test_normal_delete_bypasses_approval_and_hold() {
    FakeExecutionBoundary execution;
    FakeApprovalBoundary approval;
    FakePendingStore pending;

    DeleteTool tool(execution, pending, approval);

    auto request = approvalRequest();
    request.executionMode = DeleteExecutionMode::Immediate;
    request.approvalDecision = DeleteApprovalDecision::None;

    const auto result = tool.execute(request);

    assert(result.outcome() == DeleteOutcome::Deleted);
    assert(execution.calls == 1);
    assert(approval.calls == 0);
    assert(pending.holdCalls == 0);
}

static void test_approval_without_evidence_is_rejected() {
    FakeExecutionBoundary execution;
    FakeApprovalBoundary approval;
    FakePendingStore pending;

    DeleteTool tool(execution, pending, approval);
    auto request = approvalRequest();
    request.approvalDecision = DeleteApprovalDecision::Approved;

    const auto result = tool.execute(request);

    assert(result.error() == DeleteError::MissingAuthority);
    assert(execution.calls == 0);
}

int main() {
    test_pending_does_not_delete();
    test_repeated_pending_request_does_not_duplicate_approval();
    test_approval_commits_delete();
    test_rejection_releases_without_delete();
    test_normal_delete_bypasses_approval_and_hold();
    test_approval_without_evidence_is_rejected();

    std::cout << "BOT_04_DELETE_APPROVAL_WORKFLOW_TEST=PASS\n";
    return 0;
}
