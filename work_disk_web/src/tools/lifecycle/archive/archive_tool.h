#pragma once

#include "archive_boundaries.h"

namespace work_disk::tools::archive {

class ArchiveTool final {
public:
    ArchiveTool(const ArchiveAuthority& authority,
                ArchiveStore& store,
                ArchiveExecutor& executor)
        : authority_(authority), store_(store), executor_(executor) {}

    ArchiveResult handle(const ArchiveCommand& command) const;

private:
    const ArchiveAuthority& authority_;
    ArchiveStore& store_;
    ArchiveExecutor& executor_;

    static bool valid(const ArchiveCommand& command);
};

} // namespace work_disk::tools::archive
