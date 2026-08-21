#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace work_disk::tools::action_board {

enum class ActionResultCode {
    ActionsAvailable,
    Empty,
    InvalidRequest,
    AuthorityRejected,
    ExecutionUnavailable,
};

struct ActionContext {
    std::string context_type;
    std::string context_reference;
};

struct SelectedSet {
    std::string selection_reference;
    std::uint32_t selected_count{0};
    bool all_in_scope{false};
};

struct ActionDescriptor {
    std::string action_id;
    std::string label;
    std::string tool_reference;
};

struct ActionBoardCommand {
    std::string request_id;
    std::string authority_reference;
    ActionContext context;
    SelectedSet selection;
};

struct ActionBoardResult {
    ActionResultCode code{ActionResultCode::InvalidRequest};
    std::vector<ActionDescriptor> actions;
};

} // namespace work_disk::tools::action_board
