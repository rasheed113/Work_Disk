#include "delete_result.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::lifecycle::delete_tool;

static constexpr const char* REQUEST_ID = "REQ-RESULT-CONTRACT-001";

static void test_deleted_invariant() {
    const auto result = DeleteResult::deleted(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Deleted);
    assert(result.error() == DeleteError::None);
    assert(result.succeeded());
}

static void test_already_deleted_invariant() {
    const auto result = DeleteResult::alreadyDeleted(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::AlreadyDeleted);
    assert(result.error() == DeleteError::None);
    assert(result.succeeded());
}

static void test_not_found_is_non_success_without_error() {
    const auto result = DeleteResult::notFound(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::NotFound);
    assert(result.error() == DeleteError::None);
    assert(!result.succeeded());
}

static void test_pending_approval_is_not_deletion_success() {
    const auto result = DeleteResult::pendingApproval(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::PendingApproval);
    assert(result.error() == DeleteError::ApprovalPending);
    assert(!result.succeeded());
}

static void test_rejected_is_not_deletion_success() {
    const auto result = DeleteResult::rejected(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Rejected);
    assert(result.error() == DeleteError::ApprovalRejected);
    assert(!result.succeeded());
}

static void test_invalid_request_invariant() {
    const auto result = DeleteResult::invalidRequest(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::InvalidRequest);
    assert(!result.succeeded());
}

static void test_missing_authority_invariant() {
    const auto result = DeleteResult::missingAuthority(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::MissingAuthority);
    assert(!result.succeeded());
}

static void test_approval_failure_invariant() {
    const auto result = DeleteResult::approvalFailure(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::ApprovalFailure);
    assert(!result.succeeded());
}

static void test_pending_operation_failure_invariant() {
    const auto result = DeleteResult::pendingOperationFailure(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::PendingOperationFailure);
    assert(!result.succeeded());
}

static void test_pending_operation_conflict_invariant() {
    const auto result = DeleteResult::pendingOperationConflict(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::PendingOperationConflict);
    assert(!result.succeeded());
}

static void test_persistence_failure_invariant() {
    const auto result = DeleteResult::persistenceFailure(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::PersistenceFailure);
    assert(!result.succeeded());
}

static void test_transaction_failure_invariant() {
    const auto result = DeleteResult::transactionFailure(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::TransactionFailure);
    assert(!result.succeeded());
}

static void test_boundary_failure_invariant() {
    const auto result = DeleteResult::boundaryFailure(REQUEST_ID);
    assert(result.outcome() == DeleteOutcome::Failed);
    assert(result.error() == DeleteError::BoundaryFailure);
    assert(!result.succeeded());
}

int main() {
    test_deleted_invariant();
    test_already_deleted_invariant();
    test_not_found_is_non_success_without_error();
    test_pending_approval_is_not_deletion_success();
    test_rejected_is_not_deletion_success();
    test_invalid_request_invariant();
    test_missing_authority_invariant();
    test_approval_failure_invariant();
    test_pending_operation_failure_invariant();
    test_pending_operation_conflict_invariant();
    test_persistence_failure_invariant();
    test_transaction_failure_invariant();
    test_boundary_failure_invariant();

    std::cout << "BOT_04_DELETE_RESULT_CONTRACT_TEST=PASS\n";
    return 0;
}
