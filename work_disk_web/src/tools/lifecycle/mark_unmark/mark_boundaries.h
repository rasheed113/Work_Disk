#pragma once

#include "mark_types.h"

namespace work_disk::tools::mark {

class MarkAuthority {
public:
    virtual ~MarkAuthority() = default;
    virtual bool authorised(const std::string& authority_reference,
                            const std::string& scope_reference) const = 0;
};

class MarkSelectionStore {
public:
    virtual ~MarkSelectionStore() = default;
    virtual bool mark(const MarkCommand& command) = 0;
    virtual bool unmark(const UnmarkCommand& command) = 0;
    virtual bool mark_all(const MarkAllCommand& command) = 0;
    virtual bool clear(const ClearCommand& command) = 0;
    virtual SelectionSnapshot snapshot(const std::string& scope_reference) const = 0;
};

} // namespace work_disk::tools::mark
