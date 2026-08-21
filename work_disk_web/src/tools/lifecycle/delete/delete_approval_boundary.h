#pragma once

#include "delete_request.h"

namespace work_disk::tools::lifecycle::delete_tool {

struct DeleteApprovalResult {
    DeleteApprovalDecision decision;
    const char* failureCode;
    const char* approvalEvidence;

    static DeleteApprovalResult pending() noexcept {
        return {DeleteApprovalDecision::Pending, nullptr, nullptr};
    }

    static DeleteApprovalResult approved(const char* evidence) noexcept {
        return {DeleteApprovalDecision::Approved, nullptr, evidence};
    }

    static DeleteApprovalResult rejected(const char* evidence) noexcept {
        return {DeleteApprovalDecision::Rejected, nullptr, evidence};
    }

    static DeleteApprovalResult failed(const char* code) noexcept {
        return {DeleteApprovalDecision::None, code, nullptr};
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
