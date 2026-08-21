#pragma once

#include "edit_types.h"

namespace work_disk::tools::edit {

class EditAuthority {
public:
    virtual ~EditAuthority() = default;
    virtual bool authorised(const EditCommand& command) const = 0;
};

class EditStore {
public:
    virtual ~EditStore() = default;
    virtual EditResult begin(const EditCommand& command) = 0;
    virtual EditResult complete(const EditCommand& command,
                                const EditResult& execution_result) = 0;
};

class EditExecutor {
public:
    virtual ~EditExecutor() = default;
    virtual EditResult execute(const EditCommand& command) = 0;
};

} // namespace work_disk::tools::edit
