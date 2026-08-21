#pragma once

#include "trash_entry.h"

#include <string>
#include <vector>

namespace work_disk::tools::lifecycle::trash_tool {

enum class TrashClaimResult {
    Claimed,
    NotFound,
    Conflict,
    StorageFailure
};

class TrashStore {
public:
    virtual ~TrashStore() = default;

    virtual bool put(const TrashEntry& entry) = 0;
    virtual bool find(const std::string& itemId, TrashEntry& entry) const = 0;
    virtual std::vector<TrashEntry> list() const = 0;
    virtual TrashClaimResult claimForRestore(const std::string& itemId, TrashEntry& entry) = 0;
    virtual TrashClaimResult claimForDestruction(const std::string& itemId, TrashEntry& entry) = 0;
    virtual bool completeRestore(const std::string& itemId) = 0;
    virtual bool completeDestruction(const std::string& itemId) = 0;
    virtual bool releaseClaim(const std::string& itemId) = 0;
};

class TrashRetentionPolicy {
public:
    virtual ~TrashRetentionPolicy() = default;
    virtual bool expiresAt(TrashTime deletedAt, TrashTime& result) const = 0;
};

class TrashRestoreBoundary {
public:
    virtual ~TrashRestoreBoundary() = default;
    virtual bool restore(const TrashEntry& entry) = 0;
};

class TrashDestructionBoundary {
public:
    virtual ~TrashDestructionBoundary() = default;
    virtual bool destroy(const TrashEntry& entry) = 0;
};

} // namespace work_disk::tools::lifecycle::trash_tool
