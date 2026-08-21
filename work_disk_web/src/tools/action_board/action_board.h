#pragma once

#include "action_boundaries.h"

namespace work_disk::tools::action_board {

class ActionBoard {
public:
    ActionBoard(const ActionAuthority& authority, const ActionProvider& provider);

    ActionBoardResult discover(const ActionBoardCommand& command) const;

private:
    const ActionAuthority& authority_;
    const ActionProvider& provider_;
};

} // namespace work_disk::tools::action_board
