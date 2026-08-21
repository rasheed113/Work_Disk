#pragma once

namespace work_disk::tools::lifecycle::trash_tool {

enum class TrashError {
    None,
    InvalidRequest,
    MissingAuthority,
    StorageFailure,
    LifecycleConflict,
    RestoreFailure,
    DestructionFailure,
    RetentionPolicyFailure
};

} // namespace work_disk::tools::lifecycle::trash_tool
