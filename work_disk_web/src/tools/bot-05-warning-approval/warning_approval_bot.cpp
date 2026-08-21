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
           !request.decisionConsumerId.empty() &&
           !request.actionFingerprint.empty();
}

bool validDecision(const ApprovalDecisionInput& input) {
    return !input.approvalRequestId.empty() &&
           !input.approverId.empty() &&
           !input.authenticatedDecisionReference.empty() &&
           !input.actionFingerprint.empty() &&
           (input.decision == ApprovalDecision::Approved ||
            input.decision == ApprovalDecision::Rejected);
}

} // namespace

WarningApprovalBot::WarningApprovalBot(
    ApprovalStore& store,
    CallerAuthorizationBoundary& callerAuthorization,
    DecisionAuthenticationBoundary& decisionAuthentication,
    NotificationBoundary& notification,
    DecisionConsumerBoundary& decisionConsumer
) noexcept
    : store_(store),
      callerAuthorization_(callerAuthorization),
      decisionAuthentication_(decisionAuthentication),
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

    if (!callerAuthorization_.authorizeCaller(request)) {
        result.createStatus = ApprovalCreateStatus::UnauthorisedCaller;
        return result;
    }

    result.createStatus = store_.createPending(request);

    if (result.createStatus == ApprovalCreateStatus::AlreadyExists) {
        ApprovalState existing;
        if (!store_.find(request.approvalRequestId, existing)) {
            result.createStatus = ApprovalCreateStatus::StoreFailure;
            return result;
        }

        result.state = existing;

        // Notification delivery is transport and may be retried safely when
        // the notification layer itself provides request-id idempotency.
        if (existing.decision == ApprovalDecision::Pending &&
            !notification_.sendApprovalRequest(existing.request)) {
            result.createStatus = ApprovalCreateStatus::NotificationFailure;
        }
        return result;
    }

    if (result.createStatus != ApprovalCreateStatus::Created) {
        return result;
    }

    if (!notification_.sendApprovalRequest(request)) {
        result.createStatus = ApprovalCreateStatus::NotificationFailure;
        result.state.request = request;
        result.state.decision = ApprovalDecision::Pending;
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

    ApprovalState current;
    if (!store_.find(input.approvalRequestId, current)) {
        result.decisionStatus = ApprovalDecisionStatus::UnknownRequest;
        return result;
    }

    if (current.request.actionFingerprint != input.actionFingerprint) {
        result.decisionStatus = ApprovalDecisionStatus::RequestContextMismatch;
        result.state = current;
        return result;
    }

    if (!decisionAuthentication_.authenticateDecision(input, current)) {
        result.decisionStatus = ApprovalDecisionStatus::UnauthenticatedDecision;
        result.state = current;
        return result;
    }

    ApprovalState committed;
    result.decisionStatus = store_.commitDecisionIfPending(input, committed);
    result.state = committed;

    switch (result.decisionStatus) {
        case ApprovalDecisionStatus::Approved:
        case ApprovalDecisionStatus::Rejected:
        case ApprovalDecisionStatus::IdempotentApproved:
        case ApprovalDecisionStatus::IdempotentRejected:
            // A committed terminal decision is never rolled back because a
            // consumer is temporarily unavailable. Re-delivery is safe because
            // the decision is immutable and the action consumer must be
            // idempotent for the same approvalRequestId.
            if (!decisionConsumer_.deliverDecision(committed)) {
                result.decisionStatus = ApprovalDecisionStatus::DispatchFailure;
            }
            return result;

        case ApprovalDecisionStatus::UnknownRequest:
        case ApprovalDecisionStatus::InvalidDecision:
        case ApprovalDecisionStatus::UnauthenticatedDecision:
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

    if (approvalRequestId.empty() || !store_.find(approvalRequestId, state)) {
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
