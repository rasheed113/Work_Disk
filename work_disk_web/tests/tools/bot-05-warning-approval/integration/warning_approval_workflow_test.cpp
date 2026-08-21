#include "warning_approval_bot.h"

#include <cassert>
#include <map>
#include <string>

using namespace work_disk::tools::bot05;

class Store final : public ApprovalStore {
public:
    ApprovalCreateStatus createPending(const ApprovalRequest& request) override {
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
        ApprovalState& state
    ) override {
        const auto it = states.find(input.approvalRequestId);
        if (it == states.end()) return ApprovalDecisionStatus::UnknownRequest;
        state = it->second;
        if (state.request.approverId != input.approverId) {
            return ApprovalDecisionStatus::ApproverMismatch;
        }
        if (state.decision != ApprovalDecision::Pending) {
            return state.decision == input.decision
                ? (input.decision == ApprovalDecision::Approved
                    ? ApprovalDecisionStatus::IdempotentApproved
                    : ApprovalDecisionStatus::IdempotentRejected)
                : ApprovalDecisionStatus::DecisionConflict;
        }
        state.decision = input.decision;
        it->second = state;
        return input.decision == ApprovalDecision::Approved
            ? ApprovalDecisionStatus::Approved
            : ApprovalDecisionStatus::Rejected;
    }

private:
    std::map<std::string, ApprovalState> states;
};

class Notification final : public NotificationBoundary {
public:
    bool sendApprovalRequest(const ApprovalRequest&) override {
        ++calls;
        return available;
    }
    bool available = true;
    int calls = 0;
};

class ActionConsumer final : public DecisionConsumerBoundary {
public:
    bool deliverDecision(const ApprovalState& state) override {
        ++calls;
        last = state;
        return true;
    }
    int calls = 0;
    ApprovalState last{};
};

int main() {
    Store store;
    Notification notification;
    ActionConsumer consumer;
    WarningApprovalBot bot(store, notification, consumer);

    const ApprovalRequest request{
        "APR-FLEET-001",
        "FLEET-BOT",
        "DELETE",
        "FLEET_ENTRY",
        "ENTRY-123",
        "CONTRACTOR-77",
        "Fleet entry deletion requires contractor approval.",
        "FREEZE-BOT-DECISION-ROUTE"
    };

    const auto created = bot.createWarning(request);
    assert(created.createStatus == ApprovalCreateStatus::Created);
    assert(created.state.decision == ApprovalDecision::Pending);
    assert(consumer.calls == 0);

    // The warning has not executed the delete and has not called Freeze Bot.
    // Only the decision consumer receives the eventual signal.
    const auto rejected = bot.receiveDecision({
        "APR-FLEET-001",
        "CONTRACTOR-77",
        ApprovalDecision::Rejected,
        "SIGNED-DECISION-001"
    });

    assert(rejected.decisionStatus == ApprovalDecisionStatus::Rejected);
    assert(consumer.calls == 1);
    assert(consumer.last.state.decision == ApprovalDecision::Rejected);
    assert(consumer.last.state.request.targetId == "ENTRY-123");

    // Notification failure does not become rejection and does not create
    // an action signal.
    notification.available = false;
    const auto failedDelivery = bot.createWarning({
        "APR-SOCIAL-002",
        "SOCIAL-BOT",
        "DELETE",
        "SOCIAL_POST",
        "POST-99",
        "ACCOUNT-7",
        "Confirm post deletion.",
        "SOCIAL-ACTION-CONSUMER"
    });
    assert(failedDelivery.createStatus == ApprovalCreateStatus::NotificationFailure);
    assert(consumer.calls == 1);

    const auto stillPending = bot.query("APR-SOCIAL-002");
    assert(stillPending.queryStatus == ApprovalQueryStatus::Pending);

    return 0;
}
