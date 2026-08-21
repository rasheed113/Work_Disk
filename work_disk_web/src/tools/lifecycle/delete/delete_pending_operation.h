#pragma once

#include "delete_request.h"

#include <string>

namespace work_disk::tools::lifecycle::delete_tool {

enum class PendingOperationOutcome {
    Held,
    AlreadyHeld,
    Approved,
    Released,
    Completed,
    Missing,
    Conflict,
    Failure
};

class DeletePendingOperationStore {
public:
    virtual ~DeletePendingOperationStore() = default;

    virtual PendingOperationOutcome hold(
        const DeleteRequest& request
    ) = 0;

    virtual PendingOperationOutcome markApproved(
        const std::string& requestId,
        const std::string& approvalEvidence
    ) = 0;

    virtual PendingOperationOutcome release(
        const std::string& requestId
    ) = 0;

    virtual bool isHeld(
        const std::string& requestId
    ) const = 0;

    virtual bool isApproved(
        const std::string& requestId
    ) const = 0;

    virtual PendingOperationOutcome complete(
        const std::string& requestId
    ) = 0;
};

} // namespace work_disk::tools::lifecycle::delete_tool
