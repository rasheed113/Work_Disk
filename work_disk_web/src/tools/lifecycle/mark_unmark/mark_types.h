#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace work_disk::tools::mark {

enum class MarkResultCode {
    Marked,
    Unmarked,
    AlreadyMarked,
    AlreadyUnmarked,
    MarkAllApplied,
    Cleared,
    InvalidRequest,
    InvalidScope,
    AuthorityRejected,
    SelectionConflict,
};

enum class SelectionMode {
    Individual,
    AllInScope,
};

struct MarkTarget {
    std::string target_type;
    std::string target_id;
};

struct MarkCommand {
    std::string request_id;
    std::string authority_reference;
    std::string scope_reference;
    MarkTarget target;
};

struct MarkAllCommand {
    std::string request_id;
    std::string authority_reference;
    std::string scope_reference;
};

struct UnmarkCommand {
    std::string request_id;
    std::string authority_reference;
    std::string scope_reference;
    MarkTarget target;
};

struct ClearCommand {
    std::string request_id;
    std::string authority_reference;
    std::string scope_reference;
};

struct SelectionSnapshot {
    SelectionMode mode{SelectionMode::Individual};
    std::string scope_reference;
    std::vector<MarkTarget> targets;
};

struct MarkResult {
    MarkResultCode code{MarkResultCode::InvalidRequest};
    SelectionSnapshot selection{};
};

} // namespace work_disk::tools::mark
