# Work_Disk Web — Tools — BOT-04
# Delete Bot — Implementation Contract

## 1. Implementation Authority

BOT-04 implementation follows:

1. Approved Work_Disk architecture
2. BLUEPRINT.md
3. This Implementation Contract

If an implementation decision is undefined by those sources:

> STOP — do not guess.

## 2. Public Request Model

`DeleteRequest` contains:

- `requestId`
- `targetType`
- `targetId`
- `executionMode`
- `approvalDecision`
- `authority.authorityReference`
- `authority.approvalEvidence`

`executionMode` is authoritative input, not a hardcoded BOT-04 policy.

`Immediate` requests must not carry an approval decision or approval evidence.

`ApprovalRequired` requests begin with `None`; later approval application uses `Approved` or `Rejected` together with non-empty approval evidence.

## 3. Normal Execution

For `Immediate` mode BOT-04 must:

1. validate the request
2. require the authority reference
3. reject approval decision/evidence fields
4. call the authoritative deletion boundary
5. map its result exactly

No pending-operation hold and no Warning & Approval call occurs on this path.

## 4. Approval-Gated Execution

For `ApprovalRequired` mode BOT-04 must:

1. validate the request and authority reference
2. create a durable pending hold through `DeletePendingOperationStore`
3. call `DeleteApprovalBoundary::requestApproval` only for a newly held request
4. return `PendingApproval` when the decision is pending
5. apply `Approved` only with non-empty authoritative approval evidence
6. execute deletion only after the held operation is marked approved
7. complete the pending operation only after authoritative deletion succeeds
8. apply `Rejected` only with non-empty authoritative approval evidence
9. release the held operation on rejection
10. never call the deletion boundary on rejection

## 5. Warning & Approval Boundary

BOT-04 depends on an abstract `DeleteApprovalBoundary`.

This boundary represents the Warning & Approval Bot and prevents Delete Bot from depending on notification/UI implementation details.

The approval boundary may return:

- Pending
- Approved + approval evidence
- Rejected + approval evidence
- Failure

Approval failure must not cause deletion.

## 6. Pending Operation Boundary

`DeletePendingOperationStore` is the persistence boundary for held deletion operations.

It must support:

- hold
- mark approved
- release
- query held state
- query approved state
- complete

The production implementation must be durable according to the applicable Work_Disk persistence architecture. An in-memory fake is acceptable only for unit tests.

No expiry is introduced by BOT-04.

## 7. Commit / Release Semantics

Approval is not deletion.

`Approved` means the held operation may cross the authoritative deletion boundary.

`Rejected` means the held operation is released without reconstructing the target.

If deletion fails after approval, the operation must not be reported as completed. The approved pending state remains available for an authoritative retry according to the persistence contract.

## 8. Authority and Evidence

An identifier alone is never sufficient authority.

Approval evidence is not accepted as authority for a different request. The pending-operation identity and original target remain bound to the request identifier.

BOT-04 does not cryptographically interpret evidence; the applicable authority boundary establishes its validity.

## 9. Idempotency

The same request identifier must map to one pending deletion lifecycle.

Repeated initial approval requests while held must not duplicate the approval call.

Repeated approved execution must not repeat successful destructive effects.

Approval decisions for missing/conflicting pending operations must fail safely.

## 10. Result Contract

`DeleteOutcome` includes:

- `Deleted`
- `AlreadyDeleted`
- `NotFound`
- `PendingApproval`
- `Rejected`
- `Failed`

`DeleteError` distinguishes:

- invalid request
- missing authority
- invalid target
- approval pending
- approval rejected
- approval failure
- pending-operation failure
- pending-operation conflict
- persistence failure
- transaction failure
- boundary failure

`PendingApproval` and `Rejected` are not successful deletion outcomes.

## 11. Existing Execution Boundary

`DeleteExecutionBoundary` remains responsible for authoritative target validation and deletion execution.

BOT-04 does not move domain deletion logic into the tool.

## 12. Domain Boundaries

BOT-04 must not implement:

- Fleet approval policy
- Contractor authority
- ownership
- permissions
- authentication
- notifications
- Mark/Mark All
- Archive
- Trash
- Restore
- UI
- arbitrary cascade semantics
- universal cleanup

## 13. Testing Requirements

Tests must cover:

- normal delete executes immediately
- normal delete does not call approval
- normal delete does not create a hold
- approval-required request is held before deletion
- pending approval never reaches deletion
- repeated pending request does not duplicate approval
- approved request executes deletion
- approved deletion completes the hold only after successful deletion
- rejected request releases the hold
- rejected request never reaches deletion
- missing approval evidence is rejected
- approval failure does not delete
- execution failure after approval does not report success
- conflicting/missing pending operation is rejected
- already-deleted remains idempotent
- authority failures never reach destructive execution
- public result mapping remains explicit

## 14. Completion Gate

Complete BOT-04 only when:

- Blueprint is updated and internally consistent
- this contract is satisfied
- code is complete
- unit tests pass
- integration tests pass
- README is updated
- PROFILE is updated
- no hardcoded approval policy exists
- no unrelated responsibility exists
- repository diff is clean
- changes are committed and pushed
