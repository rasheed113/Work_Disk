#pragma once

#include "archive_types.h"

namespace work_disk::tools::archive {

class ArchiveAuthority {
public:
    virtual ~ArchiveAuthority() = default;
    virtual bool authorised(const ArchiveCommand& command) const = 0;
};

class ArchiveStore {
public:
    virtual ~ArchiveStore() = default;
    virtual ArchiveResult archive(const ArchiveCommand& command) = 0;
    virtual ArchiveResult unarchive(const ArchiveCommand& command) = 0;
};

class ArchiveExecutor {
public:
    virtual ~ArchiveExecutor() = default;
    virtual ArchiveResult execute(const ArchiveCommand& command) = 0;
};

} // namespace work_disk::tools::archive
