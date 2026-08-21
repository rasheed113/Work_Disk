#pragma once

#include "delete_request.h"

#include <string>

namespace work_disk::tools::lifecycle::delete_tool {

struct DeleteApprovalResult {
    DeleteApprovalDecision decision;
    std::string approvalEvidence;
    bool failed = false;

    static DeleteApprovalResult pending() {
        return {DeleteApprovalDecision::Pending, {}, false};
    }

    static DeleteApprovalResult approved(
        std::string evidence
    ) {
        return {DeleteApprovalDecision::Approved, std::move(evidence), false};
    }

    static DeleteApprovalResult rejected(
        std::string evidence
    ) {
        return {DeleteApprovalDecision::Rejected, std::move(evidence), false};
    }

    static DeleteApprovalResult failure() {
        return {DeleteApprovalDecision::None, {}, true};
    }
};

class DeleteApprovalBoundary {
public:
    virtual ~DeleteApprovalBoundary() = default;

    virtual DeleteApprovalResult requestApproval(
        const DeleteRequest& request
    ) = 0;
};

} // namespace work_disk::tools::lifecycle::delete_tool
