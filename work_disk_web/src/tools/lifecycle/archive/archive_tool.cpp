#include "archive_tool.h"

namespace work_disk::tools::archive {

bool ArchiveTool::valid(const ArchiveCommand& command) {
    return !command.request_id.empty()
        && !command.target_type.empty()
        && !command.target_id.empty()
        && !command.authority_reference.empty()
        && !command.source_reference.empty()
        && command.expected_version > 0;
}

ArchiveResult ArchiveTool::handle(const ArchiveCommand& command) const {
    if (!valid(command)) {
        return {ArchiveResultCode::InvalidRequest, 0};
    }

    if (!authority_.authorised(command)) {
        return {ArchiveResultCode::AuthorityRejected, 0};
    }

    const auto begin_result = store_.begin(command);
    switch (begin_result.code) {
        case ArchiveResultCode::AlreadyArchived:
        case ArchiveResultCode::AlreadyUnarchived:
            return begin_result;
        case ArchiveResultCode::NotFound:
        case ArchiveResultCode::VersionConflict:
        case ArchiveResultCode::LifecycleConflict:
        case ArchiveResultCode::InvalidRequest:
        case ArchiveResultCode::AuthorityRejected:
            return begin_result;
        default:
            break;
    }

    const auto execution_result = executor_.execute(command);
    if (execution_result.code == ArchiveResultCode::ExecutionFailed ||
        execution_result.code == ArchiveResultCode::VersionConflict ||
        execution_result.code == ArchiveResultCode::LifecycleConflict ||
        execution_result.code == ArchiveResultCode::NotFound) {
        return execution_result;
    }

    return store_.complete(command, execution_result);
}

} // namespace work_disk::tools::archive
