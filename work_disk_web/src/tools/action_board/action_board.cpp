#include "action_board.h"

namespace work_disk::tools::action_board {

ActionBoard::ActionBoard(const ActionAuthority& authority, const ActionProvider& provider)
    : authority_(authority), provider_(provider) {}

ActionBoardResult ActionBoard::discover(const ActionBoardCommand& command) const {
    ActionBoardResult result;

    if (command.request_id.empty() ||
        command.authority_reference.empty() ||
        command.context.context_type.empty() ||
        command.context.context_reference.empty() ||
        command.selection.selection_reference.empty() ||
        (command.selection.selected_count == 0 && !command.selection.all_in_scope)) {
        result.code = ActionResultCode::InvalidRequest;
        return result;
    }

    if (!authority_.allows(command.authority_reference, command.context, command.selection)) {
        result.code = ActionResultCode::AuthorityRejected;
        return result;
    }

    result.code = provider_.discover(command, result.actions);
    if (result.code == ActionResultCode::ActionsAvailable && result.actions.empty()) {
        result.code = ActionResultCode::Empty;
    }
    return result;
}

} // namespace work_disk::tools::action_board
