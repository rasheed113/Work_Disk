#pragma once

#include "delete_request.h"

namespace work_disk::tools::lifecycle::delete_tool {

enum class DeleteExecutionOutcome {
    Deleted,
    AlreadyDeleted,
    NotFound,
    ExecutionFailed
};

enum class DeleteExecutionError {
    None,
    PersistenceFailure,
    TransactionFailure,
    BoundaryFailure
};

class DeleteExecutionResult {
public:
    static DeleteExecutionResult deleted();
    static DeleteExecutionResult alreadyDeleted();
    static DeleteExecutionResult notFound();
    static DeleteExecutionResult persistenceFailure();
    static DeleteExecutionResult transactionFailure();
    static DeleteExecutionResult boundaryFailure();

    DeleteExecutionOutcome outcome() const noexcept;
    DeleteExecutionError error() const noexcept;

    bool succeeded() const noexcept;

private:
    DeleteExecutionResult(
        DeleteExecutionOutcome outcome,
        DeleteExecutionError error
    );

    DeleteExecutionOutcome outcome_;
    DeleteExecutionError error_;
};

class DeleteExecutionBoundary {
public:
    virtual ~DeleteExecutionBoundary() = default;

    virtual DeleteExecutionResult execute(
        const DeleteRequest& request
    ) = 0;
};

} // namespace work_disk::tools::lifecycle::delete_tool
