# Work_Disk Web — Tools — BOT-05
# Warning & Approval Bot — Implementation Contract

## 1. Implementation Authority

Implementation follows, in order:

1. Approved Work_Disk architecture and laws.
2. `BLUEPRINT.md`.
3. This contract.
4. The public header/API defined by this implementation.

If destructive, authority-bearing, or otherwise undefined behaviour is encountered:

> STOP — do not guess.

## 2. Public API Boundary

The public bot must expose only these workflow capabilities:

- create an approval request;
- accept a decision for an existing request;
- query the current state of an existing request.

The public API must not expose target mutation, deletion, freezing, notification transport internals, or permission administration.

## 3. Request Contract

A create request requires non-empty:

- `approvalRequestId`;
- `callerId`;
- `actionType`;
- `targetType`;
- `targetId`;
- `approverId`;
- `warningMessage`;
- `decisionConsumerId`;
- `actionFingerprint`.

The caller also supplies a decision consumer reference. This is a correlation/dispatch boundary, not an authority grant.

The caller must pass caller authorisation before the request is persisted.

The same request ID must not be rebound to different request content.

## 4. Notification Contract

BOT-05 invokes an injected notification boundary.

Notification delivery must receive the approval request and return a delivery result.

Delivery success does not change approval state.

BOT-05 must never interpret:

- notification sent;
- notification delivered;
- notification opened;
- notification read

as approval.

Notification retry must remain bound to the same approval request ID.

## 5. Decision Contract

The decision boundary accepts only:

- `Approved`;
- `Rejected`.

A decision must contain:

- approval request ID;
- approver ID;
- decision;
- authenticated decision reference;
- action fingerprint.

The decision authentication boundary must authenticate the actual approving principal. A caller-supplied approver name or non-empty reference is not authentication.

The implementation must verify exact action-fingerprint correlation with the original request before terminal state transition.

## 6. No Expiry

BOT-05 must not implement automatic expiry, timeout rejection, timeout approval, or lease-based approval semantics.

A pending request remains pending until a valid terminal decision or an explicitly authorised cancellation path exists.

Cancellation is not part of the initial public API unless separately approved.

## 7. Single Terminal Decision

The first valid terminal decision establishes the request's terminal state.

A repeated identical decision returns an idempotent result and may re-deliver the same immutable decision to the registered consumer for transport recovery.

A conflicting second decision is rejected as a decision conflict and cannot overwrite the established state.

## 8. Multi-Caller Isolation

The implementation must support concurrent requests from multiple callers.

Every request is independently keyed by `approvalRequestId`.

No caller may read, mutate, or decide another caller's request unless the supplied decision authority explicitly identifies that request.

## 9. Action Isolation

BOT-05 returns a decision; it does not execute an action.

The implementation must contain no direct dependency on:

- Delete Bot;
- Freeze Bot;
- Fleet mutation code;
- Social mutation code;
- other domain action executors.

## 10. State Machine

Allowed transitions:

```text
Pending -> Approved
Pending -> Rejected
Approved -> Approved       (idempotent replay)
Rejected -> Rejected       (idempotent replay)
Approved -> Rejected       (reject conflict)
Rejected -> Approved       (approve conflict)
```

No other transition is valid.

## 11. Persistence Boundary

The production implementation must use an authoritative approval store abstraction.

The bot must not assume process memory is durable.

The store abstraction must provide atomic create-if-absent and compare-and-set style decision transition semantics.

## 12. Decision Dispatch

After a valid terminal decision is committed, the bot emits the decision to the registered decision consumer through the injected dispatch boundary.

If consumer dispatch fails after the decision is durably committed, the decision is not reverted. Re-delivery of the same immutable terminal decision is permitted and must remain idempotent at the action consumer.

## 13. Security Requirements

Tests must demonstrate:

- request identity binding;
- caller authentication boundary;
- caller isolation;
- approver authentication boundary;
- approver binding;
- target binding;
- exact action-fingerprint binding;
- decision replay resistance;
- conflicting decision rejection;
- pending-not-approved behaviour;
- notification-success-not-approval behaviour;
- notification-failure-not-rejection behaviour;
- restart does not manufacture approval;
- no action execution inside BOT-05.

## 14. Completion Gate

BOT-05 is complete only when:

- Blueprint is satisfied;
- implementation contract is satisfied;
- attack matrix is reviewed;
- unit tests pass;
- integration tests pass;
- public API boundary is verified;
- no domain action dependency exists;
- README and PROFILE are complete;
- repository checks pass.
