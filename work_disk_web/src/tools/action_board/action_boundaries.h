#pragma once

#include "action_types.h"

namespace work_disk::tools::action_board {

class ActionAuthority {
public:
    virtual ~ActionAuthority() = default;
    virtual bool allows(const std::string& authority_reference,
                        const ActionContext& context,
                        const SelectedSet& selection) const = 0;
};

class ActionProvider {
public:
    virtual ~ActionProvider() = default;
    virtual ActionResultCode discover(const ActionBoardCommand& command,
                                      std::vector<ActionDescriptor>& actions) const = 0;
};

} // namespace work_disk::tools::action_board
