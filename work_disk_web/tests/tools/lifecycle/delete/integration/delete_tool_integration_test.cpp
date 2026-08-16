#include "delete_tool.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::lifecycle::delete_tool;

class AuthoritativeDeleteBoundary final : public DeleteExecutionBoundary {
public:
    bool called = false;
    bool targetValidated = false;
    DeleteRequest receivedRequest{};

    DeleteExecutionResult execute(
        const DeleteRequest& request
    ) override {
        called = true;
        receivedRequest = request;

        // This boundary represents the authoritative domain deletion contract.
        // Target validation and authoritative deletion happen here.
        if (request.targetType.empty() || request.targetId.empty()) {
            return DeleteExecutionResult::boundaryFailure();
        }

        targetValidated = true;

        return DeleteExecutionResult::deleted();
    }
};

static DeleteRequest make_authorised_request() {
    DeleteRequest request;

    request.requestId = "REQ-BOT04-INTEGRATION-001";
    request.targetType = "FleetEntry";
    request.targetId = "ENTRY-123456";

    request.authority.authorityReference =
        "OPAQUE-AUTHORITY-REFERENCE";

    request.authority.approvalEvidence =
        "OPAQUE-APPROVAL-EVIDENCE";

    return request;
}

static void test_complete_authorised_deletion_boundary() {
    AuthoritativeDeleteBoundary boundary;
    DeleteTool tool(boundary);

    const auto request = make_authorised_request();
    const auto result = tool.execute(request);

    // Authorised request reached the authoritative boundary.
    assert(boundary.called);

    // Target validation occurred inside the authoritative boundary.
    assert(boundary.targetValidated);

    // The request crossed the boundary unchanged.
    assert(
        boundary.receivedRequest.requestId ==
        request.requestId
    );

    assert(
        boundary.receivedRequest.targetType ==
        request.targetType
    );

    assert(
        boundary.receivedRequest.targetId ==
        request.targetId
    );

    assert(
        boundary.receivedRequest.authority.authorityReference ==
        request.authority.authorityReference
    );

    assert(
        boundary.receivedRequest.authority.approvalEvidence ==
        request.authority.approvalEvidence
    );

    // BOT-04 reports only the authoritative result.
    assert(result.outcome() == DeleteOutcome::Deleted);
    assert(result.error() == DeleteError::None);
    assert(result.succeeded());
    assert(result.requestId() == request.requestId);
}

static void test_missing_authority_never_reaches_execution() {
    AuthoritativeDeleteBoundary boundary;
    DeleteTool tool(boundary);

    auto request = make_authorised_request();
    request.authority.authorityReference.clear();

    const auto result = tool.execute(request);

    assert(!boundary.called);
    assert(!boundary.targetValidated);

    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::MissingAuthority);
    assert(!result.succeeded());
}

static void test_authoritative_execution_failure_never_becomes_success() {
    class FailingBoundary final : public DeleteExecutionBoundary {
    public:
        bool called = false;

        DeleteExecutionResult execute(
            const DeleteRequest&
        ) override {
            called = true;
            return DeleteExecutionResult::transactionFailure();
        }
    };

    FailingBoundary boundary;
    DeleteTool tool(boundary);

    const auto result = tool.execute(make_authorised_request());

    assert(boundary.called);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::TransactionFailure);
    assert(!result.succeeded());
}

int main() {
    test_complete_authorised_deletion_boundary();
    test_missing_authority_never_reaches_execution();
    test_authoritative_execution_failure_never_becomes_success();

    std::cout
        << "BOT_04_DELETE_TOOL_INTEGRATION_TEST=PASS\n";

    return 0;
}
