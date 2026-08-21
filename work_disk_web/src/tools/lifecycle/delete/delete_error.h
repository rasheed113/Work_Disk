#pragma once

namespace work_disk::tools::lifecycle::delete_tool {

enum class DeleteError {
    None,

    InvalidRequest,
    MissingAuthority,
    InvalidTarget,

    ApprovalPending,
    ApprovalRejected,
    ApprovalFailure,
    PendingOperationFailure,
    PendingOperationConflict,

    PersistenceFailure,
    TransactionFailure,
    BoundaryFailure
};

} // namespace work_disk::tools::lifecycle::delete_tool
