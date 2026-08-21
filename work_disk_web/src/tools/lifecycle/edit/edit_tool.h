#pragma once

#include "edit_boundaries.h"

namespace work_disk::tools::edit {

class EditTool final {
public:
    EditTool(const EditAuthority& authority,
             EditStore& store,
             EditExecutor& executor)
        : authority_(authority), store_(store), executor_(executor) {}

    EditResult handle(const EditCommand& command) const;

private:
    const EditAuthority& authority_;
    EditStore& store_;
    EditExecutor& executor_;

    static bool valid(const EditCommand& command);
};

} // namespace work_disk::tools::edit
