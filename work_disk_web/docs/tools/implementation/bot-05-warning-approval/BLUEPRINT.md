# Work_Disk Web — Tools — BOT-05
# Warning & Approval Bot — Architecture Blueprint

## 1. Identity

BOT-05 is the **Warning & Approval Bot**.

BOT-05 is a reusable tool bot. It accepts authorised calls from multiple domain/tool bots and provides one bounded warning-and-approval workflow.

Core rule:

> Warning & Approval Bot creates the approval gate; it never performs the gated action.

## 2. Purpose

BOT-05:

- creates a warning/approval request for a caller;
- records the exact action context supplied by the caller;
- asks the Notification Bot/System to deliver the approval request;
- receives the final approval decision through its public decision boundary;
- returns the single decision to the registered action consumer.

BOT-05 does not delete, freeze, restore, allocate, revoke, transfer, publish, or otherwise execute the protected action.

## 3. Multi-Caller Boundary

BOT-05 MUST support multiple authorised callers.

The caller is identified per request and must not be hard-coded to Fleet, Delete Bot, Social, or any single domain.

Each request is isolated by a unique `approvalRequestId`.

A caller may create many independent approval requests. Multiple callers may have pending requests concurrently.

## 4. Public Workflow

```text
Authorised Caller
    -> BOT-05 Warning & Approval Bot
    -> Notification Boundary
    -> Target Approver
    -> Notification/Decision Boundary
    -> BOT-05
    -> Registered Decision Consumer
```

The registered decision consumer is the component that owns the pending action. BOT-05 does not assume that component is Freeze Bot.

## 5. Warning Boundary

A warning request must identify, at minimum:

- approval request ID;
- caller identity;
- action type;
- target type;
- target ID;
- approver identity/reference;
- human-readable warning context;
- notification reference after delivery.

The warning payload may contain enough target information for the approver to make an informed decision, subject to the caller/domain privacy contract.

BOT-05 does not reconstruct hidden domain state.

## 6. Approval Semantics

Approval is a binary terminal decision:

- `Approved` = positive signal;
- `Rejected` = negative signal.

No third terminal meaning may be invented.

Pending is an intermediate workflow state, not approval.

Approval has **no expiry** under the current architecture.

A pending request remains pending until an authorised decision is accepted or the owning domain explicitly cancels it through a separately authorised cancellation path.

## 7. Single-Decision Rule

An approval request may transition from `Pending` to exactly one terminal decision.

Once `Approved` or `Rejected`, the request is immutable for decision purposes.

Repeated identical delivery of the same decision must be idempotent.

A conflicting second decision must not overwrite the first decision.

## 8. Authority Boundary

BOT-05 does not decide who is entitled to approve.

Approver identity and approval authority are established by the caller/domain authority and supplied as request context.

BOT-05 may validate structural completeness and request ownership, but it must not invent permissions or roles.

## 9. Notification Boundary

BOT-05 does not implement notification transport.

It invokes a notification boundary with the approval request.

The notification component is responsible for delivery and for returning an authenticated approval decision to BOT-05.

Notification delivery success is not approval.

Notification failure is not rejection.

## 10. Action Boundary

BOT-05 never executes the protected action.

It MUST NOT:

- call Delete Bot to delete a target;
- call Freeze Bot to freeze/unfreeze a target;
- mutate the target;
- perform rollback;
- perform compensation;
- grant authority;
- revoke authority;
- infer approval from timeout, silence, notification read status, or user presence.

The action owner consumes the decision and performs the action under its own authority boundary.

## 11. Decision Routing Boundary

The original caller registers the decision consumer for the approval request.

BOT-05 returns exactly the terminal decision associated with that request to that consumer.

The consumer receives no implicit authority beyond the decision itself.

## 12. Security Invariants

- Unknown approval request IDs are rejected.
- Unknown callers are rejected according to the caller-authentication boundary.
- Decisions for another request cannot be applied to this request.
- A decision for one target cannot be rebound to another target.
- A decision cannot change caller identity, action type, target type, or target ID.
- Notification transport is not trusted as action authority.
- Duplicate decisions are idempotent.
- Conflicting replayed decisions cannot overwrite an established terminal state.
- Pending requests cannot be treated as approved.
- Silence cannot be treated as approval.
- Approval cannot be treated as action completion.

## 13. Privacy / Data Minimisation

BOT-05 stores only the approval context required by the approved workflow and audit contract.

Full domain records must not be copied into BOT-05 merely for convenience.

The target ID/reference is the primary correlation mechanism.

## 14. Failure Semantics

If warning creation fails, no approval workflow is considered active.

If notification delivery fails, the request remains pending; delivery failure is not rejection.

If a decision cannot be authenticated or correlated, it is rejected and the request remains pending.

If a conflicting terminal decision is received after a terminal decision already exists, the original decision remains authoritative and the conflict is recorded according to the audit contract.

Undefined failure semantics require STOP — do not guess.

## 15. Concurrency

Multiple requests may be pending concurrently.

State transitions for one request must be atomic with respect to competing decisions.

A decision for request A must never affect request B.

## 16. Recovery

BOT-05 must not manufacture approval after restart.

Pending requests must be recoverable from the authoritative approval store in a production implementation.

If the authoritative request state is unavailable or ambiguous, BOT-05 must not promote the request to Approved.

## 17. Explicit Non-Responsibilities

BOT-05 does not own:

- deletion;
- freezing/unfreezing;
- notification transport;
- authentication;
- identity management;
- ownership decisions;
- permission decisions;
- Fleet business rules;
- Social business rules;
- compensation/rollback;
- action execution;
- UI confirmation rendering;
- expiry/timeouts.

## 18. Architectural Principle

> A warning creates a gate. An approval opens the gate. A rejection closes the gate. The gate never performs the action.
