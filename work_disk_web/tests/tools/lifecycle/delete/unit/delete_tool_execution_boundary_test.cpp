#include "delete_tool.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::lifecycle::delete_tool;

class SpyExecutionBoundary final
    : public DeleteExecutionBoundary {
public:
    bool called = false;
    DeleteRequest receivedRequest{};

    DeleteExecutionResult nextResult =
        DeleteExecutionResult::deleted();

    DeleteExecutionResult execute(
        const DeleteRequest& request
    ) override {
        called = true;
        receivedRequest = request;
        return nextResult;
    }
};

static DeleteRequest make_valid_request() {
    DeleteRequest request;

    request.requestId = "REQ-BOT04-BOUNDARY-001";
    request.targetType = "SocialPost";
    request.targetId = "POST-123456";

    request.authority.authorityReference =
        "OPAQUE-AUTHORITY-REFERENCE";

    return request;
}

static void test_deleted_reaches_boundary() {
    SpyExecutionBoundary boundary;
    boundary.nextResult =
        DeleteExecutionResult::deleted();

    DeleteTool tool(boundary);
    const auto request = make_valid_request();

    const auto result = tool.execute(request);

    assert(boundary.called);

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

    assert(result.outcome() == DeleteOutcome::Deleted);
    assert(result.error() == DeleteError::None);
    assert(result.succeeded());
    assert(result.requestId() == request.requestId);
}

static void test_already_deleted_mapping() {
    SpyExecutionBoundary boundary;
    boundary.nextResult =
        DeleteExecutionResult::alreadyDeleted();

    DeleteTool tool(boundary);

    const auto result =
        tool.execute(make_valid_request());

    assert(result.outcome() == DeleteOutcome::AlreadyDeleted);
    assert(result.error() == DeleteError::None);
    assert(result.succeeded());
}

static void test_not_found_mapping() {
    SpyExecutionBoundary boundary;
    boundary.nextResult =
        DeleteExecutionResult::notFound();

    DeleteTool tool(boundary);

    const auto result =
        tool.execute(make_valid_request());

    assert(result.outcome() == DeleteOutcome::NotFound);
    assert(result.error() == DeleteError::None);
    assert(!result.succeeded());
}

static void test_invalid_request_does_not_reach_boundary() {
    SpyExecutionBoundary boundary;

    DeleteTool tool(boundary);

    DeleteRequest request =
        make_valid_request();

    request.requestId.clear();

    const auto result =
        tool.execute(request);

    assert(!boundary.called);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::InvalidRequest);
}

static void test_missing_authority_does_not_reach_boundary() {
    SpyExecutionBoundary boundary;

    DeleteTool tool(boundary);

    DeleteRequest request =
        make_valid_request();

    request.authority.authorityReference.clear();

    const auto result =
        tool.execute(request);

    assert(!boundary.called);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::MissingAuthority);
}

int main() {
    test_deleted_reaches_boundary();
    test_already_deleted_mapping();
    test_not_found_mapping();
    test_invalid_request_does_not_reach_boundary();
    test_missing_authority_does_not_reach_boundary();

    std::cout
        << "BOT_04_DELETE_TOOL_EXECUTION_BOUNDARY_TEST=PASS\n";

    return 0;
}
