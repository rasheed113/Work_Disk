# Work_Disk Web — Tools — BOT-04
# Delete Bot — Architecture Blueprint

## 1. Purpose & Scope

BOT-04 is the Delete Bot.

BOT-04 provides a strictly bounded deletion execution boundary for Work_Disk.
It supports two execution paths:

1. **Normal Delete** — execute an already-authorised deletion immediately.
2. **Approval-Gated Delete** — hold the requested deletion without deleting the target, request approval through the Warning & Approval Bot boundary, and commit or release the held operation from the authoritative approval result.

The governing principle is:

> Authority decides. Delete Bot controls the deletion lifecycle and executes only the authorised result.

BOT-04 does not decide whether a resource should be deleted or who is entitled to approve it.

BOT-04 is not an Archive Bot, Trash Manager, Restore Handler, Mark Bot, Filter, Sort, or universal cleanup/orchestration component.

## 2. Core Invariants

The following rules are non-negotiable:

- BOT-04 only executes deletion within established authority.
- BOT-04 does not create domain authority.
- The authorised execution mode determines whether deletion is immediate or approval-gated; the mode is not hardcoded by BOT-04.
- Normal deletion reaches the authoritative deletion boundary without an approval hold.
- Approval-gated deletion never reaches the destructive execution boundary before approval.
- A held target remains existing; hold means the deletion operation is pending, not that the target has already been deleted.
- Approval acceptance commits the held deletion.
- Approval rejection releases the hold; it does not recreate or paste back a deleted target because no deletion occurred while the operation was held.
- The action-owning Delete Bot owns the pending deletion lifecycle; a separate Freeze Bot is not required for this lifecycle.
- Warning & Approval Bot owns warning/approval decision generation, not deletion execution.
- Approval evidence must be bound to the same deletion request before an approval decision can commit or release the held operation.
- A pending operation has no expiry unless a future architecture explicitly introduces one.
- Repeated initial calls for an already-held request must not create duplicate approval requests.
- Repeated approved execution must remain safely idempotent.
- If authoritative deletion fails after approval, the held operation must not be reported as completed merely because approval succeeded.
- BOT-04 must not report successful deletion before authoritative deletion has completed.
- Presentation expiry is never interpreted as deletion.
- Protected historical or evidence data cannot be silently destroyed.
- Archive, Trash, Restore, Mark, and UI behaviour remain outside BOT-04.
- Undefined destructive behaviour requires STOP; BOT-04 must not guess.

## 3. Authority Boundary

The relevant domain or upstream authority establishes whether deletion is permitted and whether approval is required.

BOT-04 consumes that established authority context and follows the declared execution mode. It must not:

- invent authority
- grant authority
- bypass authority
- weaken approval requirements
- replace domain authority
- choose an approver
- decide an approval outcome
- perform ownership decisions
- perform permission decisions

## 4. Approval Boundary

BOT-04 may call the Warning & Approval Bot only through an explicit approval boundary.

The Warning & Approval Bot is responsible for:

- creating the warning
- requesting the approval decision through its own notification workflow
- returning the authoritative positive or negative approval result

BOT-04 is responsible for:

- holding the deletion before approval
- preventing destructive execution while approval is pending
- accepting the authoritative approval evidence
- committing deletion after approval
- releasing the held deletion after rejection

BOT-04 must not manufacture an approval result.

## 5. Fleet Boundary

Fleet-specific approval remains a domain policy decision.

If a Fleet deletion is marked approval-required by the applicable authoritative policy, BOT-04 uses the approval-gated path. The Contractor/Fleet domain remains responsible for determining the required authority and approver.

The Delete Bot must not hardcode Fleet-specific approval logic.

## 6. Conceptual Request Contract

A deletion request requires:

- unique request identity
- target type
- target identifier
- authoritative authority reference
- execution mode
- approval decision state
- approval evidence when a positive or negative approval decision is being applied

Conceptual shape:

```text
DeleteRequest
├── requestId
├── targetType
├── targetId
├── executionMode
│   ├── Immediate
│   └── ApprovalRequired
├── approvalDecision
│   ├── None
│   ├── Pending
│   ├── Approved
│   └── Rejected
└── authority
    ├── authorityReference
    └── approvalEvidence
```

The exact representation of authority and approval evidence is an implementation contract decision. BOT-04 must not assume a particular cryptographic or transport mechanism unless separately authorised.

## 7. Hold Semantics

For an approval-required request, the target remains authoritative and existing.

The held state means:

> **Deletion requested, deletion not yet executed, approval pending.**

Freeze/hold is therefore a property of the deletion operation, not a deletion of the target.

BOT-04 owns this lifecycle through its pending-operation boundary.

## 8. Execution Lifecycle

### Normal

```text
Request
  → validate authority/context
  → authoritative deletion execution
  → result
```

### Approval-Gated

```text
Request
  → validate authority/context
  → hold pending deletion
  → Warning & Approval Bot
  → Pending
       ↓
   Approved → commit deletion → complete held operation
       ↓
   Rejected → release held operation → target remains
```

Approval success is not itself deletion success. The authoritative deletion boundary must still complete successfully.

## 9. Idempotency

The same request identifier represents the same deletion operation.

- Repeating the initial approval-gated request while already held must not create another approval request.
- Repeating an approved request must not cause repeated destructive effects.
- Replaying an approval result against a missing or incompatible pending operation must be rejected.
- Idempotency must never weaken authority or approval-evidence checks.

## 10. Failure & Safety

Malformed requests, missing authority, invalid targets, invalid approval evidence, pending-operation conflicts, approval failures, and authoritative execution failures must be explicit.

If approval infrastructure fails, the held operation remains unresolved rather than being silently deleted or silently released.

Undefined destructive behaviour requires:

> STOP — do not guess.

## 11. Atomicity Boundary

BOT-04 must respect the atomicity guarantees of the authoritative persistence layer.

The hold state and its approval lifecycle must be persisted through the pending-operation boundary where durable state is required. BOT-04 must not claim universal rollback across independent systems unless the architecture explicitly provides it.

## 12. Preservation Boundary

Approval rejection does not require reconstruction of the target because the target was never deleted while held.

Protected historical/evidence records remain subject to their domain preservation rules.

Presentation cleanup or projection reset is outside BOT-04.

## 13. Domain Separation

BOT-04 does not own:

- Account authority
- Identity authority
- Fleet authority
- Contractor authority
- Approval policy
- Notification delivery
- Mark/selection state
- Archive lifecycle
- Trash lifecycle
- Restore lifecycle
- Permissions
- UI behaviour
- Domain business rules

## 14. Explicit Non-Responsibilities

BOT-04 does not:

- decide whether approval is required
- choose the approver
- generate approval outcomes
- send notifications directly
- perform ownership decisions
- invent cascade behaviour
- implement Mark or Mark All
- become Delete All orchestration outside an authorised domain scope
- become a universal cleanup engine
- become a general orchestration engine

## 15. Security Boundary

Calling BOT-04 does not grant deletion authority.

No destructive execution may occur unless the request has the required authority and, for approval-gated operations, authoritative approval evidence.

A valid approval result cannot expand the target scope beyond the original authorised deletion request.

## 16. Public Boundary

Consumers interact through the Delete Bot public contract.

Internal persistence, pending-operation storage, approval transport, and authoritative deletion mechanisms remain implementation details behind their respective boundaries.

## 17. Principle

BOT-04 follows this rule:

> **Normal action executes normally. Approval-required action is held by the action-owning bot until an authoritative approval decision commits or releases it.**

Domain authority decides. Warning & Approval Bot decides approval. Delete Bot owns the deletion lifecycle and executes.
