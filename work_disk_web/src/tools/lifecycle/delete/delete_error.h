#pragma once

namespace work_disk::tools::lifecycle::delete_tool {

enum class DeleteError {
    None,

    InvalidRequest,
    MissingAuthority,
    InvalidTarget,

    PersistenceFailure,
    TransactionFailure,
    BoundaryFailure
};

} // namespace work_disk::tools::lifecycle::delete_tool
