#pragma once

#include "approval_request.h"

namespace work_disk::tools::bot05 {

class ApprovalStore {
public:
    virtual ~ApprovalStore() = default;

    virtual ApprovalCreateStatus createPending(const ApprovalRequest& request) = 0;

    virtual bool find(
        const std::string& approvalRequestId,
        ApprovalState& state
    ) const = 0;

    virtual ApprovalDecisionStatus commitDecisionIfPending(
        const ApprovalDecisionInput& input,
        ApprovalState& committedState
    ) = 0;
};

class NotificationBoundary {
public:
    virtual ~NotificationBoundary() = default;

    virtual bool sendApprovalRequest(
        const ApprovalRequest& request
    ) = 0;
};

class DecisionConsumerBoundary {
public:
    virtual ~DecisionConsumerBoundary() = default;

    virtual bool deliverDecision(
        const ApprovalState& state
    ) = 0;
};

} // namespace work_disk::tools::bot05
