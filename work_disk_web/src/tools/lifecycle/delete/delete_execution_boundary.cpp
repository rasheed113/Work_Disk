#include "delete_execution_boundary.h"

namespace work_disk::tools::lifecycle::delete_tool {

DeleteExecutionResult::DeleteExecutionResult(
    DeleteExecutionOutcome outcome,
    DeleteExecutionError error
)
    : outcome_(outcome),
      error_(error) {}

DeleteExecutionResult DeleteExecutionResult::deleted() {
    return DeleteExecutionResult(
        DeleteExecutionOutcome::Deleted,
        DeleteExecutionError::None
    );
}

DeleteExecutionResult DeleteExecutionResult::alreadyDeleted() {
    return DeleteExecutionResult(
        DeleteExecutionOutcome::AlreadyDeleted,
        DeleteExecutionError::None
    );
}

DeleteExecutionResult DeleteExecutionResult::notFound() {
    return DeleteExecutionResult(
        DeleteExecutionOutcome::NotFound,
        DeleteExecutionError::None
    );
}

DeleteExecutionResult DeleteExecutionResult::persistenceFailure() {
    return DeleteExecutionResult(
        DeleteExecutionOutcome::ExecutionFailed,
        DeleteExecutionError::PersistenceFailure
    );
}

DeleteExecutionResult DeleteExecutionResult::transactionFailure() {
    return DeleteExecutionResult(
        DeleteExecutionOutcome::ExecutionFailed,
        DeleteExecutionError::TransactionFailure
    );
}

DeleteExecutionResult DeleteExecutionResult::boundaryFailure() {
    return DeleteExecutionResult(
        DeleteExecutionOutcome::ExecutionFailed,
        DeleteExecutionError::BoundaryFailure
    );
}

DeleteExecutionOutcome
DeleteExecutionResult::outcome() const noexcept {
    return outcome_;
}

DeleteExecutionError
DeleteExecutionResult::error() const noexcept {
    return error_;
}

bool DeleteExecutionResult::succeeded() const noexcept {
    return outcome_ == DeleteExecutionOutcome::Deleted ||
           outcome_ == DeleteExecutionOutcome::AlreadyDeleted;
}

} // namespace work_disk::tools::lifecycle::delete_tool
