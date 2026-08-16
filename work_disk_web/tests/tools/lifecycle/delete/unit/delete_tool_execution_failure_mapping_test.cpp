#include "delete_tool.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::lifecycle::delete_tool;

class FailureSpyBoundary final
    : public DeleteExecutionBoundary {
public:
    DeleteExecutionResult nextResult =
        DeleteExecutionResult::boundaryFailure();

    DeleteExecutionResult execute(
        const DeleteRequest&
    ) override {
        return nextResult;
    }
};

static DeleteRequest make_valid_request() {
    DeleteRequest request;

    request.requestId = "REQ-BOT04-FAILURE-MAP-001";
    request.targetType = "FleetEntry";
    request.targetId = "ENTRY-123456";

    request.authority.authorityReference =
        "OPAQUE-AUTHORITY-REFERENCE";

    request.authority.approvalEvidence =
        "OPAQUE-APPROVAL-EVIDENCE";

    return request;
}

static void test_persistence_failure_mapping() {
    FailureSpyBoundary boundary;

    boundary.nextResult =
        DeleteExecutionResult::persistenceFailure();

    DeleteTool tool(boundary);

    const auto result =
        tool.execute(make_valid_request());

    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::PersistenceFailure);
    assert(!result.succeeded());
}

static void test_transaction_failure_mapping() {
    FailureSpyBoundary boundary;

    boundary.nextResult =
        DeleteExecutionResult::transactionFailure();

    DeleteTool tool(boundary);

    const auto result =
        tool.execute(make_valid_request());

    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::TransactionFailure);
    assert(!result.succeeded());
}

static void test_boundary_failure_mapping() {
    FailureSpyBoundary boundary;

    boundary.nextResult =
        DeleteExecutionResult::boundaryFailure();

    DeleteTool tool(boundary);

    const auto result =
        tool.execute(make_valid_request());

    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::BoundaryFailure);
    assert(!result.succeeded());
}

static void test_invalid_execution_failure_is_not_reported_as_success() {
    FailureSpyBoundary boundary;

    boundary.nextResult =
        DeleteExecutionResult::transactionFailure();

    DeleteTool tool(boundary);

    const auto result =
        tool.execute(make_valid_request());

    assert(!result.succeeded());
    assert(result.outcome() == DeleteOutcome::Failed);
}

int main() {
    test_persistence_failure_mapping();
    test_transaction_failure_mapping();
    test_boundary_failure_mapping();
    test_invalid_execution_failure_is_not_reported_as_success();

    std::cout
        << "BOT_04_DELETE_TOOL_EXECUTION_FAILURE_MAPPING_TEST=PASS\n";

    return 0;
}
