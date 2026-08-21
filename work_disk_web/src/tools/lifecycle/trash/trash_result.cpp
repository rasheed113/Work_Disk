#include "trash_result.h"

#include <utility>

namespace work_disk::tools::lifecycle::trash_tool {

TrashResult::TrashResult(
    std::string operationId,
    TrashOutcome outcome,
    TrashError error,
    std::size_t remaining
) : operationId_(std::move(operationId)),
    outcome_(outcome),
    error_(error),
    remaining_(remaining) {}

TrashResult TrashResult::stored(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::Stored, TrashError::None, 0);
}
TrashResult TrashResult::restored(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::Restored, TrashError::None, 0);
}
TrashResult TrashResult::alreadyRestored(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::AlreadyRestored, TrashError::None, 0);
}
TrashResult TrashResult::destroyed(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::Destroyed, TrashError::None, 0);
}
TrashResult TrashResult::alreadyDestroyed(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::AlreadyDestroyed, TrashError::None, 0);
}
TrashResult TrashResult::notFound(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::NotFound, TrashError::None, 0);
}
TrashResult TrashResult::expired(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::Expired, TrashError::None, 0);
}
TrashResult TrashResult::emptied(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::Emptied, TrashError::None, 0);
}
TrashResult TrashResult::partiallyEmptied(std::string operationId, std::size_t remaining) {
    return TrashResult(std::move(operationId), TrashOutcome::PartiallyEmptied, TrashError::DestructionFailure, remaining);
}
TrashResult TrashResult::purged(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::Purged, TrashError::None, 0);
}
TrashResult TrashResult::nothingToPurge(std::string operationId) {
    return TrashResult(std::move(operationId), TrashOutcome::NothingToPurge, TrashError::None, 0);
}
TrashResult TrashResult::failed(std::string operationId, TrashError error) {
    return TrashResult(std::move(operationId), TrashOutcome::Failed, error, 0);
}

TrashOutcome TrashResult::outcome() const noexcept { return outcome_; }
TrashError TrashResult::error() const noexcept { return error_; }
bool TrashResult::succeeded() const noexcept {
    return outcome_ == TrashOutcome::Stored ||
           outcome_ == TrashOutcome::Restored ||
           outcome_ == TrashOutcome::AlreadyRestored ||
           outcome_ == TrashOutcome::Destroyed ||
           outcome_ == TrashOutcome::AlreadyDestroyed ||
           outcome_ == TrashOutcome::Emptied ||
           outcome_ == TrashOutcome::Purged ||
           outcome_ == TrashOutcome::NothingToPurge;
}
std::size_t TrashResult::remaining() const noexcept { return remaining_; }
const std::string& TrashResult::operationId() const noexcept { return operationId_; }

} // namespace work_disk::tools::lifecycle::trash_tool
