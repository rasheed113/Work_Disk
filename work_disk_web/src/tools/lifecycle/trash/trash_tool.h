#pragma once

#include "trash_boundaries.h"
#include "trash_result.h"

namespace work_disk::tools::lifecycle::trash_tool {

class TrashTool {
public:
    TrashTool(
        TrashStore& store,
        TrashRetentionPolicy& retentionPolicy,
        TrashRestoreBoundary& restoreBoundary,
        TrashDestructionBoundary& destructionBoundary
    ) noexcept;

    TrashResult intake(const std::string& operationId, const TrashEntryInput& input) const;
    TrashResult restore(const std::string& operationId, const TrashAuthority& authority, const std::string& itemId, TrashTime now) const;
    TrashResult deleteOne(const std::string& operationId, const TrashAuthority& authority, const std::string& itemId) const;
    TrashResult empty(const std::string& operationId, const TrashAuthority& authority) const;
    TrashResult purgeExpired(const std::string& operationId, const TrashAuthority& authority, TrashTime now) const;

private:
    bool validAuthority(const TrashAuthority& authority) const noexcept;
    bool validInput(const TrashEntryInput& input) const noexcept;
    TrashResult destroyClaimed(const std::string& operationId, const TrashEntry& entry) const;

    TrashStore& store_;
    TrashRetentionPolicy& retentionPolicy_;
    TrashRestoreBoundary& restoreBoundary_;
    TrashDestructionBoundary& destructionBoundary_;
};

} // namespace work_disk::tools::lifecycle::trash_tool
