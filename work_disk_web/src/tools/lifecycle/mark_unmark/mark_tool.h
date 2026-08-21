#pragma once

#include "mark_boundaries.h"

namespace work_disk::tools::mark {

class MarkTool {
public:
    MarkTool(const MarkAuthority& authority, MarkSelectionStore& store)
        : authority_(authority), store_(store) {}

    static bool valid(const MarkCommand& command);
    static bool valid(const UnmarkCommand& command);
    static bool valid(const MarkAllCommand& command);
    static bool valid(const ClearCommand& command);

    MarkResult mark(const MarkCommand& command) const;
    MarkResult unmark(const UnmarkCommand& command) const;
    MarkResult mark_all(const MarkAllCommand& command) const;
    MarkResult clear(const ClearCommand& command) const;

private:
    bool authorised(const std::string& authority_reference,
                    const std::string& scope_reference) const;
    const MarkAuthority& authority_;
    MarkSelectionStore& store_;
};

} // namespace work_disk::tools::mark
