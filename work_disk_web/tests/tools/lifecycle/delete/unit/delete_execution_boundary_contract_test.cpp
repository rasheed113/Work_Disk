#include "delete_execution_boundary.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::lifecycle::delete_tool;

class SpyExecutionBoundary final : public DeleteExecutionBoundary {
public:
    DeleteRequest received_request{};
    bool called = false;

    DeleteExecutionResult execute(
        const DeleteRequest& request
    ) override {
        called = true;
        received_request = request;

        return DeleteExecutionResult::deleted();
    }
};

static DeleteRequest make_request() {
    DeleteRequest request;

    request.requestId = "REQ-OPAQUE-001";
    request.targetType = "FleetEntry";
    request.targetId = "ENTRY-123456";

    request.authority.authorityReference =
        "OPAQUE-AUTHORITY-REFERENCE-847";

    request.authority.approvalEvidence =
        "OPAQUE-APPROVAL-EVIDENCE-XYZ";

    return request;
}

static void test_request_is_received_unchanged() {
    SpyExecutionBoundary boundary;

    const auto request = make_request();
    const auto result = boundary.execute(request);

    assert(boundary.called);

    assert(
        boundary.received_request.requestId ==
        request.requestId
    );

    assert(
        boundary.received_request.targetType ==
        request.targetType
    );

    assert(
        boundary.received_request.targetId ==
        request.targetId
    );

    assert(
        boundary.received_request.authority.authorityReference ==
        request.authority.authorityReference
    );

    assert(
        boundary.received_request.authority.approvalEvidence ==
        request.authority.approvalEvidence
    );

    assert(
        result.outcome() ==
        DeleteExecutionOutcome::Deleted
    );

    assert(result.error() == DeleteExecutionError::None);
    assert(result.succeeded());
}

int main() {
    test_request_is_received_unchanged();

    std::cout
        << "BOT_04_DELETE_EXECUTION_BOUNDARY_CONTRACT_TEST=PASS\n";

    return 0;
}
