#include "delete_tool.h"

#include <cassert>
#include <iostream>
#include <string>

using namespace work_disk::tools::lifecycle::delete_tool;

class AuthoritativeDeleteBoundary final : public DeleteExecutionBoundary {
public:
    bool called = false;
    bool targetValidated = false;

    DeleteExecutionResult execute(const DeleteRequest& request) override {
        called = true;
        if (request.targetType.empty() || request.targetId.empty()) {
            return DeleteExecutionResult::boundaryFailure();
        }
        targetValidated = true;
        return DeleteExecutionResult::deleted();
    }
};

class NoopPendingStore final : public DeletePendingOperationStore {
public:
    PendingOperationOutcome hold(const DeleteRequest&) override { return PendingOperationOutcome::Held; }
    PendingOperationOutcome markApproved(const std::string&, const std::string&) override { return PendingOperationOutcome::Approved; }
    PendingOperationOutcome release(const std::string&) override { return PendingOperationOutcome::Released; }
    bool isHeld(const std::string&) const override { return false; }
    bool isApproved(const std::string&) const override { return false; }
    PendingOperationOutcome complete(const std::string&) override { return PendingOperationOutcome::Completed; }
};

class NoopApprovalBoundary final : public DeleteApprovalBoundary {
public:
    DeleteApprovalResult requestApproval(const DeleteRequest&) override {
        return DeleteApprovalResult::pending();
    }
};

static DeleteRequest make_authorised_request() {
    DeleteRequest request;
    request.requestId = "REQ-BOT04-INTEGRATION-001";
    request.targetType = "FleetEntry";
    request.targetId = "ENTRY-123456";
    request.executionMode = DeleteExecutionMode::Immediate;
    request.authority.authorityReference = "OPAQUE-AUTHORITY-REFERENCE";
    return request;
}

static void test_complete_authorised_deletion_boundary() {
    AuthoritativeDeleteBoundary boundary;
    NoopPendingStore pending;
    NoopApprovalBoundary approval;
    DeleteTool tool(boundary, pending, approval);

    const auto result = tool.execute(make_authorised_request());

    assert(boundary.called);
    assert(boundary.targetValidated);
    assert(result.outcome() == DeleteOutcome::Deleted);
    assert(result.error() == DeleteError::None);
    assert(result.succeeded());
}

static void test_authoritative_execution_failure_never_becomes_success() {
    class FailingBoundary final : public DeleteExecutionBoundary {
    public:
        bool called = false;

        DeleteExecutionResult execute(const DeleteRequest&) override {
            called = true;
            return DeleteExecutionResult::transactionFailure();
        }
    };

    FailingBoundary boundary;
    NoopPendingStore pending;
    NoopApprovalBoundary approval;
    DeleteTool tool(boundary, pending, approval);

    const auto result = tool.execute(make_authorised_request());

    assert(boundary.called);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::TransactionFailure);
    assert(!result.succeeded());
}

int main() {
    test_complete_authorised_deletion_boundary();
    test_authoritative_execution_failure_never_becomes_success();

    std::cout << "BOT_04_DELETE_TOOL_INTEGRATION_TEST=PASS\n";
    return 0;
}
