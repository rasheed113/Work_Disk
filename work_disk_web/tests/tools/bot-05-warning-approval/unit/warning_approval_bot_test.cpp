#include "warning_approval_bot.h"

#include <cassert>
#include <map>
#include <string>

using namespace work_disk::tools::bot05;

class FakeCallerAuthorization final : public CallerAuthorizationBoundary {
public:
    bool authorizeCaller(const ApprovalRequest&) const override {
        return allowed;
    }
    bool allowed = true;
};

class FakeDecisionAuthentication final : public DecisionAuthenticationBoundary {
public:
    bool authenticateDecision(
        const ApprovalDecisionInput& input,
        const ApprovalState& state
    ) const override {
        return allowed &&
               input.approverId == state.request.approverId &&
               !input.authenticatedDecisionReference.empty();
    }
    bool allowed = true;
};

class FakeStore final : public ApprovalStore {
public:
    ApprovalCreateStatus createPending(const ApprovalRequest& request) override {
        if (request.approvalRequestId.empty()) {
            return ApprovalCreateStatus::InvalidRequest;
        }
        if (states.count(request.approvalRequestId) != 0U) {
            return ApprovalCreateStatus::AlreadyExists;
        }
        states.emplace(
            request.approvalRequestId,
            ApprovalState{request, ApprovalDecision::Pending}
        );
        return ApprovalCreateStatus::Created;
    }

    bool find(const std::string& id, ApprovalState& state) const override {
        const auto it = states.find(id);
        if (it == states.end()) return false;
        state = it->second;
        return true;
    }

    ApprovalDecisionStatus commitDecisionIfPending(
        const ApprovalDecisionInput& input,
        ApprovalState& committedState
    ) override {
        const auto it = states.find(input.approvalRequestId);
        if (it == states.end()) return ApprovalDecisionStatus::UnknownRequest;

        committedState = it->second;
        if (committedState.request.approverId != input.approverId) {
            return ApprovalDecisionStatus::ApproverMismatch;
        }
        if (committedState.request.actionFingerprint != input.actionFingerprint) {
            return ApprovalDecisionStatus::RequestContextMismatch;
        }

        if (committedState.decision == ApprovalDecision::Pending) {
            committedState.decision = input.decision;
            it->second = committedState;
            return input.decision == ApprovalDecision::Approved
                ? ApprovalDecisionStatus::Approved
                : ApprovalDecisionStatus::Rejected;
        }

        if (committedState.decision == input.decision) {
            return input.decision == ApprovalDecision::Approved
                ? ApprovalDecisionStatus::IdempotentApproved
                : ApprovalDecisionStatus::IdempotentRejected;
        }

        return ApprovalDecisionStatus::DecisionConflict;
    }

private:
    std::map<std::string, ApprovalState> states;
};

class FakeNotification final : public NotificationBoundary {
public:
    bool sendApprovalRequest(const ApprovalRequest&) override {
        ++sent;
        return available;
    }

    bool available = true;
    int sent = 0;
};

class FakeConsumer final : public DecisionConsumerBoundary {
public:
    bool deliverDecision(const ApprovalState& state) override {
        ++delivered;
        last = state;
        return available;
    }

    bool available = true;
    int delivered = 0;
    ApprovalState last{};
};

static ApprovalRequest request(
    const std::string& id,
    const std::string& caller,
    const std::string& target
) {
    return ApprovalRequest{
        id,
        caller,
        "DELETE",
        "FLEET_ENTRY",
        target,
        "CONTRACTOR-01",
        "Confirm requested action",
        caller + "-decision-consumer",
        "fingerprint-" + target
    };
}

int main() {
    FakeStore store;
    FakeCallerAuthorization callerAuthorization;
    FakeDecisionAuthentication decisionAuthentication;
    FakeNotification notification;
    FakeConsumer consumer;
    WarningApprovalBot bot(
        store,
        callerAuthorization,
        decisionAuthentication,
        notification,
        consumer
    );

    const auto first = bot.createWarning(
        request("APR-001", "FLEET-BOT", "ENTRY-001")
    );
    assert(first.createStatus == ApprovalCreateStatus::Created);
    assert(first.state.decision == ApprovalDecision::Pending);
    assert(notification.sent == 1);

    const auto pending = bot.query("APR-001");
    assert(pending.queryStatus == ApprovalQueryStatus::Pending);

    const auto approved = bot.receiveDecision({
        "APR-001", "CONTRACTOR-01", ApprovalDecision::Approved,
        "DEC-001", "fingerprint-ENTRY-001"
    });
    assert(approved.decisionStatus == ApprovalDecisionStatus::Approved);
    assert(approved.state.decision == ApprovalDecision::Approved);
    assert(consumer.delivered == 1);

    const auto replay = bot.receiveDecision({
        "APR-001", "CONTRACTOR-01", ApprovalDecision::Approved,
        "DEC-001", "fingerprint-ENTRY-001"
    });
    assert(replay.decisionStatus == ApprovalDecisionStatus::IdempotentApproved);
    assert(consumer.delivered == 2);

    const auto conflict = bot.receiveDecision({
        "APR-001", "CONTRACTOR-01", ApprovalDecision::Rejected,
        "DEC-002", "fingerprint-ENTRY-001"
    });
    assert(conflict.decisionStatus == ApprovalDecisionStatus::DecisionConflict);
    assert(consumer.last.decision == ApprovalDecision::Approved);

    const auto otherCaller = bot.createWarning(
        request("APR-002", "SOCIAL-BOT", "POST-001")
    );
    assert(otherCaller.createStatus == ApprovalCreateStatus::Created);
    assert(otherCaller.state.request.callerId == "SOCIAL-BOT");

    const auto spoofed = bot.receiveDecision({
        "APR-002", "ATTACKER", ApprovalDecision::Approved,
        "DEC-003", "fingerprint-POST-001"
    });
    assert(spoofed.decisionStatus == ApprovalDecisionStatus::ApproverMismatch);

    const auto rebound = bot.receiveDecision({
        "APR-002", "CONTRACTOR-01", ApprovalDecision::Approved,
        "DEC-004", "fingerprint-OTHER"
    });
    assert(rebound.decisionStatus == ApprovalDecisionStatus::RequestContextMismatch);

    callerAuthorization.allowed = false;
    const auto unauthorisedCaller = bot.createWarning(
        request("APR-003", "ATTACKER-BOT", "ENTRY-003")
    );
    assert(unauthorisedCaller.createStatus == ApprovalCreateStatus::UnauthorisedCaller);

    const auto invalid = bot.createWarning(ApprovalRequest{});
    assert(invalid.createStatus == ApprovalCreateStatus::InvalidRequest);

    return 0;
}
