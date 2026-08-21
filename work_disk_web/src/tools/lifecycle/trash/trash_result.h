#pragma once

#include "trash_error.h"

#include <cstddef>
#include <string>

namespace work_disk::tools::lifecycle::trash_tool {

enum class TrashOutcome {
    Stored,
    Restored,
    AlreadyRestored,
    Destroyed,
    AlreadyDestroyed,
    NotFound,
    Expired,
    Emptied,
    PartiallyEmptied,
    Purged,
    NothingToPurge,
    Failed
};

class TrashResult {
public:
    static TrashResult stored(std::string operationId);
    static TrashResult restored(std::string operationId);
    static TrashResult alreadyRestored(std::string operationId);
    static TrashResult destroyed(std::string operationId);
    static TrashResult alreadyDestroyed(std::string operationId);
    static TrashResult notFound(std::string operationId);
    static TrashResult expired(std::string operationId);
    static TrashResult emptied(std::string operationId);
    static TrashResult partiallyEmptied(std::string operationId, std::size_t remaining);
    static TrashResult purged(std::string operationId);
    static TrashResult nothingToPurge(std::string operationId);
    static TrashResult failed(std::string operationId, TrashError error);

    TrashOutcome outcome() const noexcept;
    TrashError error() const noexcept;
    bool succeeded() const noexcept;
    std::size_t remaining() const noexcept;
    const std::string& operationId() const noexcept;

private:
    TrashResult(std::string operationId, TrashOutcome outcome, TrashError error, std::size_t remaining);

    std::string operationId_;
    TrashOutcome outcome_;
    TrashError error_;
    std::size_t remaining_;
};

} // namespace work_disk::tools::lifecycle::trash_tool
