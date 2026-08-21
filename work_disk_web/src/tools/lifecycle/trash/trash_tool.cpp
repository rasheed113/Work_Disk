#include "trash_tool.h"

namespace work_disk::tools::lifecycle::trash_tool {

TrashTool::TrashTool(
    TrashStore& store,
    TrashRetentionPolicy& retentionPolicy,
    TrashRestoreBoundary& restoreBoundary,
    TrashDestructionBoundary& destructionBoundary
) noexcept
    : store_(store),
      retentionPolicy_(retentionPolicy),
      restoreBoundary_(restoreBoundary),
      destructionBoundary_(destructionBoundary) {}

bool TrashTool::validAuthority(const TrashAuthority& authority) const noexcept {
    return !authority.authorityReference.empty();
}

bool TrashTool::validInput(const TrashEntryInput& input) const noexcept {
    return !input.itemId.empty() &&
           !input.targetType.empty() &&
           !input.targetId.empty() &&
           !input.originalLocationReference.empty() &&
           !input.payloadReference.empty();
}

TrashResult TrashTool::intake(
    const std::string& operationId,
    const TrashEntryInput& input
) const {
    if (operationId.empty() || !validInput(input)) {
        return TrashResult::failed(operationId, TrashError::InvalidRequest);
    }

    TrashTime expiresAt{};
    if (!retentionPolicy_.expiresAt(input.deletedAt, expiresAt)) {
        return TrashResult::failed(operationId, TrashError::RetentionPolicyFailure);
    }

    TrashEntry entry{
        input.itemId,
        input.targetType,
        input.targetId,
        input.originalLocationReference,
        input.payloadReference,
        input.deletedAt,
        expiresAt
    };

    if (!store_.put(entry)) {
        return TrashResult::failed(operationId, TrashError::StorageFailure);
    }

    return TrashResult::stored(operationId);
}

TrashResult TrashTool::restore(
    const std::string& operationId,
    const TrashAuthority& authority,
    const std::string& itemId,
    TrashTime now
) const {
    if (operationId.empty() || itemId.empty()) {
        return TrashResult::failed(operationId, TrashError::InvalidRequest);
    }
    if (!validAuthority(authority)) {
        return TrashResult::failed(operationId, TrashError::MissingAuthority);
    }

    TrashEntry entry{};
    if (!store_.find(itemId, entry)) {
        return TrashResult::notFound(operationId);
    }
    if (now >= entry.expiresAt) {
        return TrashResult::expired(operationId);
    }

    const TrashClaimResult claim = store_.claimForRestore(itemId, entry);
    if (claim == TrashClaimResult::NotFound) {
        return TrashResult::notFound(operationId);
    }
    if (claim != TrashClaimResult::Claimed) {
        return TrashResult::failed(operationId, claim == TrashClaimResult::StorageFailure
            ? TrashError::StorageFailure
            : TrashError::LifecycleConflict);
    }

    if (!restoreBoundary_.restore(entry)) {
        if (!store_.releaseClaim(itemId)) {
            return TrashResult::failed(operationId, TrashError::StorageFailure);
        }
        return TrashResult::failed(operationId, TrashError::RestoreFailure);
    }

    if (!store_.completeRestore(itemId)) {
        return TrashResult::failed(operationId, TrashError::StorageFailure);
    }

    return TrashResult::restored(operationId);
}

TrashResult TrashTool::destroyClaimed(
    const std::string& operationId,
    const TrashEntry& entry
) const {
    if (!destructionBoundary_.destroy(entry)) {
        if (!store_.releaseClaim(entry.itemId)) {
            return TrashResult::failed(operationId, TrashError::StorageFailure);
        }
        return TrashResult::failed(operationId, TrashError::DestructionFailure);
    }

    if (!store_.completeDestruction(entry.itemId)) {
        return TrashResult::failed(operationId, TrashError::StorageFailure);
    }

    return TrashResult::destroyed(operationId);
}

TrashResult TrashTool::deleteOne(
    const std::string& operationId,
    const TrashAuthority& authority,
    const std::string& itemId
) const {
    if (operationId.empty() || itemId.empty()) {
        return TrashResult::failed(operationId, TrashError::InvalidRequest);
    }
    if (!validAuthority(authority)) {
        return TrashResult::failed(operationId, TrashError::MissingAuthority);
    }

    TrashEntry entry{};
    const TrashClaimResult claim = store_.claimForDestruction(itemId, entry);
    if (claim == TrashClaimResult::NotFound) {
        return TrashResult::notFound(operationId);
    }
    if (claim != TrashClaimResult::Claimed) {
        return TrashResult::failed(operationId, claim == TrashClaimResult::StorageFailure
            ? TrashError::StorageFailure
            : TrashError::LifecycleConflict);
    }

    return destroyClaimed(operationId, entry);
}

TrashResult TrashTool::empty(
    const std::string& operationId,
    const TrashAuthority& authority
) const {
    if (operationId.empty()) {
        return TrashResult::failed(operationId, TrashError::InvalidRequest);
    }
    if (!validAuthority(authority)) {
        return TrashResult::failed(operationId, TrashError::MissingAuthority);
    }

    const auto entries = store_.list();
    for (const TrashEntry& listed : entries) {
        TrashEntry claimed{};
        if (store_.claimForDestruction(listed.itemId, claimed) == TrashClaimResult::Claimed) {
            (void)destroyClaimed(operationId, claimed);
        }
    }

    const auto remaining = store_.list().size();
    if (remaining == 0) {
        return TrashResult::emptied(operationId);
    }
    return TrashResult::partiallyEmptied(operationId, remaining);
}

TrashResult TrashTool::purgeExpired(
    const std::string& operationId,
    const TrashAuthority& authority,
    TrashTime now
) const {
    if (operationId.empty()) {
        return TrashResult::failed(operationId, TrashError::InvalidRequest);
    }
    if (!validAuthority(authority)) {
        return TrashResult::failed(operationId, TrashError::MissingAuthority);
    }

    const auto entries = store_.list();
    bool foundExpired = false;
    for (const TrashEntry& listed : entries) {
        if (now < listed.expiresAt) {
            continue;
        }
        foundExpired = true;

        TrashEntry claimed{};
        if (store_.claimForDestruction(listed.itemId, claimed) == TrashClaimResult::Claimed) {
            (void)destroyClaimed(operationId, claimed);
        }
    }

    const auto remaining = store_.list().size();
    if (!foundExpired) {
        return TrashResult::nothingToPurge(operationId);
    }
    if (remaining == 0) {
        return TrashResult::purged(operationId);
    }
    return TrashResult::partiallyEmptied(operationId, remaining);
}

} // namespace work_disk::tools::lifecycle::trash_tool
