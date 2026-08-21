#include "delete_tool.h"

#include <cassert>
#include <iostream>
#include <string>

using namespace work_disk::tools::lifecycle::delete_tool;

class SpyExecutionBoundary final : public DeleteExecutionBoundary {
public:
    bool called = false;
    DeleteRequest receivedRequest{};
    DeleteExecutionResult nextResult = DeleteExecutionResult::deleted();

    DeleteExecutionResult execute(const DeleteRequest& request) override {
        called = true;
        receivedRequest = request;
        return nextResult;
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

static DeleteRequest make_valid_request() {
    DeleteRequest request;
    request.requestId = "REQ-BOT04-BOUNDARY-001";
    request.targetType = "FleetEntry";
    request.targetId = "ENTRY-123456";
    request.executionMode = DeleteExecutionMode::Immediate;
    request.authority.authorityReference = "OPAQUE-AUTHORITY-REFERENCE";
    return request;
}

static void test_deleted_reaches_boundary() {
    SpyExecutionBoundary boundary;
    NoopPendingStore pending;
    NoopApprovalBoundary approval;
    DeleteTool tool(boundary, pending, approval);

    const auto request = make_valid_request();
    const auto result = tool.execute(request);

    assert(boundary.called);
    assert(boundary.receivedRequest.requestId == request.requestId);
    assert(boundary.receivedRequest.targetType == request.targetType);
    assert(boundary.receivedRequest.targetId == request.targetId);
    assert(boundary.receivedRequest.authority.authorityReference == request.authority.authorityReference);
    assert(result.outcome() == DeleteOutcome::Deleted);
    assert(result.error() == DeleteError::None);
    assert(result.succeeded());
}

static void test_invalid_request_does_not_reach_boundary() {
    SpyExecutionBoundary boundary;
    NoopPendingStore pending;
    NoopApprovalBoundary approval;
    DeleteTool tool(boundary, pending, approval);

    auto request = make_valid_request();
    request.requestId.clear();

    const auto result = tool.execute(request);

    assert(!boundary.called);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::InvalidRequest);
}

static void test_missing_authority_does_not_reach_boundary() {
    SpyExecutionBoundary boundary;
    NoopPendingStore pending;
    NoopApprovalBoundary approval;
    DeleteTool tool(boundary, pending, approval);

    auto request = make_valid_request();
    request.authority.authorityReference.clear();

    const auto result = tool.execute(request);

    assert(!boundary.called);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::MissingAuthority);
}

int main() {
    test_deleted_reaches_boundary();
    test_invalid_request_does_not_reach_boundary();
    test_missing_authority_does_not_reach_boundary();

    std::cout << "BOT_04_DELETE_TOOL_EXECUTION_BOUNDARY_TEST=PASS\n";
    return 0;
}
