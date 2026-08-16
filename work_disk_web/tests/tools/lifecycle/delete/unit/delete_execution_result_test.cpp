#include "delete_execution_boundary.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::lifecycle::delete_tool;

static void test_deleted() {
    const auto result = DeleteExecutionResult::deleted();

    assert(result.outcome() == DeleteExecutionOutcome::Deleted);
    assert(result.error() == DeleteExecutionError::None);
    assert(result.succeeded());
}

static void test_already_deleted() {
    const auto result = DeleteExecutionResult::alreadyDeleted();

    assert(result.outcome() == DeleteExecutionOutcome::AlreadyDeleted);
    assert(result.error() == DeleteExecutionError::None);
    assert(result.succeeded());
}

static void test_not_found_is_not_success() {
    const auto result = DeleteExecutionResult::notFound();

    assert(result.outcome() == DeleteExecutionOutcome::NotFound);
    assert(result.error() == DeleteExecutionError::None);
    assert(!result.succeeded());
}

static void test_persistence_failure() {
    const auto result = DeleteExecutionResult::persistenceFailure();

    assert(result.outcome() == DeleteExecutionOutcome::ExecutionFailed);
    assert(result.error() == DeleteExecutionError::PersistenceFailure);
    assert(!result.succeeded());
}

static void test_transaction_failure() {
    const auto result = DeleteExecutionResult::transactionFailure();

    assert(result.outcome() == DeleteExecutionOutcome::ExecutionFailed);
    assert(result.error() == DeleteExecutionError::TransactionFailure);
    assert(!result.succeeded());
}

static void test_boundary_failure() {
    const auto result = DeleteExecutionResult::boundaryFailure();

    assert(result.outcome() == DeleteExecutionOutcome::ExecutionFailed);
    assert(result.error() == DeleteExecutionError::BoundaryFailure);
    assert(!result.succeeded());
}

int main() {
    test_deleted();
    test_already_deleted();
    test_not_found_is_not_success();
    test_persistence_failure();
    test_transaction_failure();
    test_boundary_failure();

    std::cout
        << "BOT_04_DELETE_EXECUTION_RESULT_CONTRACT_TEST=PASS\n";

    return 0;
}
