#pragma once

#include <cstdint>
#include <string>

namespace work_disk::tools::archive {

enum class ArchiveOperation {
    Archive,
    Unarchive,
};

enum class ArchiveResultCode {
    Archived,
    Unarchived,
    AlreadyArchived,
    AlreadyUnarchived,
    NotFound,
    AuthorityRejected,
    VersionConflict,
    InvalidRequest,
    LifecycleConflict,
    ExecutionFailed,
};

struct ArchiveCommand {
    std::string request_id;
    ArchiveOperation operation{};
    std::string target_type;
    std::string target_id;
    std::string authority_reference;
    std::string source_reference;
    std::uint64_t expected_version{0};
};

struct ArchiveResult {
    ArchiveResultCode code{ArchiveResultCode::InvalidRequest};
    std::uint64_t resulting_version{0};
};

} // namespace work_disk::tools::archive
