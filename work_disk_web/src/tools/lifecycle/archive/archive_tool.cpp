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

    // The executor owns the authoritative domain transition. The store remains
    // the durable lifecycle boundary; concrete implementations may atomically
    // claim/idempotently resolve the request before execution.
    const auto result = executor_.execute(command);
    if (result.code == ArchiveResultCode::ExecutionFailed ||
        result.code == ArchiveResultCode::VersionConflict ||
        result.code == ArchiveResultCode::LifecycleConflict ||
        result.code == ArchiveResultCode::NotFound) {
        return result;
    }

    return command.operation == ArchiveOperation::Archive
        ? store_.archive(command)
        : store_.unarchive(command);
}

} // namespace work_disk::tools::archive
