#include "mark_tool.h"

namespace work_disk::tools::mark {

namespace {
bool valid_target(const MarkTarget& target) {
    return !target.target_type.empty() && !target.target_id.empty();
}
}

bool MarkTool::valid(const MarkCommand& command) {
    return !command.request_id.empty() && !command.authority_reference.empty()
        && !command.scope_reference.empty() && valid_target(command.target);
}

bool MarkTool::valid(const UnmarkCommand& command) {
    return !command.request_id.empty() && !command.authority_reference.empty()
        && !command.scope_reference.empty() && valid_target(command.target);
}

bool MarkTool::valid(const MarkAllCommand& command) {
    return !command.request_id.empty() && !command.authority_reference.empty()
        && !command.scope_reference.empty();
}

bool MarkTool::valid(const ClearCommand& command) {
    return !command.request_id.empty() && !command.authority_reference.empty()
        && !command.scope_reference.empty();
}

bool MarkTool::authorised(const std::string& authority_reference,
                          const std::string& scope_reference) const {
    return authority_.authorised(authority_reference, scope_reference);
}

MarkResult MarkTool::mark(const MarkCommand& command) const {
    if (!valid(command)) return {MarkResultCode::InvalidRequest, {}};
    if (!authorised(command.authority_reference, command.scope_reference))
        return {MarkResultCode::AuthorityRejected, {}};
    if (!store_.mark(command)) return {MarkResultCode::SelectionConflict, {}};
    return {MarkResultCode::Marked, store_.snapshot(command.scope_reference)};
}

MarkResult MarkTool::unmark(const UnmarkCommand& command) const {
    if (!valid(command)) return {MarkResultCode::InvalidRequest, {}};
    if (!authorised(command.authority_reference, command.scope_reference))
        return {MarkResultCode::AuthorityRejected, {}};
    if (!store_.unmark(command)) return {MarkResultCode::SelectionConflict, {}};
    return {MarkResultCode::Unmarked, store_.snapshot(command.scope_reference)};
}

MarkResult MarkTool::mark_all(const MarkAllCommand& command) const {
    if (!valid(command)) return {MarkResultCode::InvalidRequest, {}};
    if (!authorised(command.authority_reference, command.scope_reference))
        return {MarkResultCode::AuthorityRejected, {}};
    if (!store_.mark_all(command)) return {MarkResultCode::SelectionConflict, {}};
    return {MarkResultCode::MarkAllApplied, store_.snapshot(command.scope_reference)};
}

MarkResult MarkTool::clear(const ClearCommand& command) const {
    if (!valid(command)) return {MarkResultCode::InvalidRequest, {}};
    if (!authorised(command.authority_reference, command.scope_reference))
        return {MarkResultCode::AuthorityRejected, {}};
    if (!store_.clear(command)) return {MarkResultCode::SelectionConflict, {}};
    return {MarkResultCode::Cleared, store_.snapshot(command.scope_reference)};
}

} // namespace work_disk::tools::mark
