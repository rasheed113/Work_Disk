#pragma once

#include "approval_boundaries.h"
#include "warning_approval_result.h"

namespace work_disk::tools::bot05 {

class WarningApprovalBot {
public:
    WarningApprovalBot(
        ApprovalStore& store,
        CallerAuthorizationBoundary& callerAuthorization,
        DecisionAuthenticationBoundary& decisionAuthentication,
        NotificationBoundary& notification,
        DecisionConsumerBoundary& decisionConsumer
    ) noexcept;

    WarningApprovalResult createWarning(
        const ApprovalRequest& request
    );

    WarningApprovalResult receiveDecision(
        const ApprovalDecisionInput& input
    );

    WarningApprovalResult query(
        const std::string& approvalRequestId
    ) const;

private:
    ApprovalStore& store_;
    CallerAuthorizationBoundary& callerAuthorization_;
    DecisionAuthenticationBoundary& decisionAuthentication_;
    NotificationBoundary& notification_;
    DecisionConsumerBoundary& decisionConsumer_;
};

} // namespace work_disk::tools::bot05
