#pragma once

#include <cstdint>
#include <string>

namespace work_disk::tools::edit {

enum class EditResultCode {
    Edited,
    NoOp,
    NotFound,
    AuthorityRejected,
    VersionConflict,
    InvalidRequest,
    LifecycleConflict,
    ExecutionFailed,
};

struct EditCommand {
    std::string request_id;
    std::string target_type;
    std::string target_id;
    std::string authority_reference;
    std::string edit_scope;
    std::string new_value;
    std::uint64_t expected_version{0};
    bool edited_marker_applicable{false};
};

struct EditResult {
    EditResultCode code{EditResultCode::InvalidRequest};
    std::uint64_t resulting_version{0};
};

} // namespace work_disk::tools::edit
