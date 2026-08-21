# Work_Disk Web — BOT-04 Delete Bot

BOT-04 is the Work_Disk deletion Tool Bot.

## Core Rule

> **Normal action executes normally. Approval-required action is held by Delete Bot until an authoritative approval decision commits or releases it.**

## Execution Modes

### Normal Delete

```text
Delete Request
  → Delete Bot
  → Authoritative Delete Boundary
  → Deleted
```

No hold and no Warning & Approval call occurs.

### Approval-Gated Delete

```text
Delete Request
  → Delete Bot holds operation
  → Warning & Approval Bot
  → Pending
       ├─ Approved → Delete Bot commits deletion
       └─ Rejected → Delete Bot releases hold
```

While held, the target remains existing. Rejection therefore does not restore the target; it simply releases an operation that never deleted it.

## Boundaries

Delete Bot owns:

- deletion lifecycle
- pending hold lifecycle
- commit after approval
- release after rejection
- authoritative deletion result mapping

Warning & Approval Bot owns:

- warning creation
- approval request flow
- positive/negative approval decision

Delete Bot does not own:

- approval policy
- approver selection
- notification delivery
- Fleet authority
- Contractor authority
- Mark/Mark All
- Archive
- Trash
- Restore
- UI behaviour
- ownership or permission decisions

## No Expiry

The approval-gated pending operation has no BOT-04 expiry. A future expiry policy would require an explicit architectural change.

## Idempotency

A request identifier represents one deletion lifecycle. Repeating a pending request does not create duplicate approval requests, and repeated successful deletion does not repeat destructive effects.

## Public Results

BOT-04 exposes explicit outcomes:

- `Deleted`
- `AlreadyDeleted`
- `NotFound`
- `PendingApproval`
- `Rejected`
- `Failed`

`PendingApproval` and `Rejected` are not successful deletion outcomes.

## Implementation Files

- `delete_request.h`
- `delete_approval_boundary.h`
- `delete_pending_operation.h`
- `delete_error.h`
- `delete_result.h`
- `delete_result.cpp`
- `delete_execution_boundary.h`
- `delete_execution_boundary.cpp`
- `delete_tool.h`
- `delete_tool.cpp`

## Verification

Verification covers both execution modes and the full approval lifecycle:

`Normal → Execute`

and

`Approval Required → Hold → Warning/Approval → Commit or Release`

No hardcoded Fleet-specific approval policy is embedded in BOT-04.
