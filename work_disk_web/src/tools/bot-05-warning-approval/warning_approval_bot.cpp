#include "warning_approval_bot.h"

namespace work_disk::tools::bot05 {

namespace {

bool validRequest(const ApprovalRequest& request) {
    return !request.approvalRequestId.empty() &&
           !request.callerId.empty() &&
           !request.actionType.empty() &&
           !request.targetType.empty() &&
           !request.targetId.empty() &&
           !request.approverId.empty() &&
           !request.warningMessage.empty() &&
           !request.decisionConsumerId.empty();
}

bool validDecision(const ApprovalDecisionInput& input) {
    return !input.approvalRequestId.empty() &&
           !input.approverId.empty() &&
           !input.authenticatedDecisionReference.empty() &&
           (input.decision == ApprovalDecision::Approved ||
            input.decision == ApprovalDecision::Rejected);
}

} // namespace

WarningApprovalBot::WarningApprovalBot(
    ApprovalStore& store,
    NotificationBoundary& notification,
    DecisionConsumerBoundary& decisionConsumer
) noexcept
    : store_(store),
      notification_(notification),
      decisionConsumer_(decisionConsumer) {}

WarningApprovalResult WarningApprovalBot::createWarning(
    const ApprovalRequest& request
) {
    WarningApprovalResult result;

    if (!validRequest(request)) {
        result.createStatus = ApprovalCreateStatus::InvalidRequest;
        return result;
    }

    result.createStatus = store_.createPending(request);

    if (result.createStatus == ApprovalCreateStatus::AlreadyExists) {
        ApprovalState existing;
        if (store_.find(request.approvalRequestId, existing)) {
            result.state = existing;
        }
        return result;
    }

    if (result.createStatus != ApprovalCreateStatus::Created) {
        return result;
    }

    if (!notification_.sendApprovalRequest(request)) {
        result.createStatus = ApprovalCreateStatus::NotificationFailure;
        return result;
    }

    result.state.request = request;
    result.state.decision = ApprovalDecision::Pending;
    return result;
}

WarningApprovalResult WarningApprovalBot::receiveDecision(
    const ApprovalDecisionInput& input
) {
    WarningApprovalResult result;

    if (!validDecision(input)) {
        result.decisionStatus = ApprovalDecisionStatus::InvalidDecision;
        return result;
    }

    ApprovalState committed;
    result.decisionStatus = store_.commitDecisionIfPending(input, committed);
    result.state = committed;

    switch (result.decisionStatus) {
        case ApprovalDecisionStatus::Approved:
        case ApprovalDecisionStatus::Rejected:
            if (!decisionConsumer_.deliverDecision(committed)) {
                result.decisionStatus = ApprovalDecisionStatus::DispatchFailure;
            }
            return result;

        case ApprovalDecisionStatus::IdempotentApproved:
        case ApprovalDecisionStatus::IdempotentRejected:
        case ApprovalDecisionStatus::UnknownRequest:
        case ApprovalDecisionStatus::InvalidDecision:
        case ApprovalDecisionStatus::ApproverMismatch:
        case ApprovalDecisionStatus::RequestContextMismatch:
        case ApprovalDecisionStatus::DecisionConflict:
        case ApprovalDecisionStatus::StoreFailure:
        case ApprovalDecisionStatus::DispatchFailure:
            return result;
    }

    result.decisionStatus = ApprovalDecisionStatus::StoreFailure;
    return result;
}

WarningApprovalResult WarningApprovalBot::query(
    const std::string& approvalRequestId
) const {
    WarningApprovalResult result;
    ApprovalState state;

    if (!store_.find(approvalRequestId, state)) {
        result.queryStatus = ApprovalQueryStatus::UnknownRequest;
        return result;
    }

    result.state = state;

    switch (state.decision) {
        case ApprovalDecision::Pending:
            result.queryStatus = ApprovalQueryStatus::Pending;
            break;
        case ApprovalDecision::Approved:
            result.queryStatus = ApprovalQueryStatus::Approved;
            break;
        case ApprovalDecision::Rejected:
            result.queryStatus = ApprovalQueryStatus::Rejected;
            break;
    }

    return result;
}

} // namespace work_disk::tools::bot05
