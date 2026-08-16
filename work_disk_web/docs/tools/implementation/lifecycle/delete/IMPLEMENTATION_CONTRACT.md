# Work_Disk Web — Tools — BOT-04
# Delete Bot — Implementation Contract

## 1. Implementation Authority

BOT-04 implementation must follow only:

1. Approved Work_Disk architecture
2. BLUEPRINT.md
3. This Implementation Contract

If implementation encounters an undefined destructive behaviour:

> STOP — do not guess.

No historical implementation assumption may override the approved
architecture.

## 2. Implementation Boundary

BOT-04 implements authorised deletion execution only.

It must not implement:

- ownership decisions
- permission decisions
- authentication
- Fleet authority
- Contractor approval
- Archive
- Trash
- Restore
- Filter
- Sort
- UI behaviour
- unrelated cleanup
- universal orchestration

## 3. Deletion Request Boundary

A deletion request must contain sufficient information to identify:

- request identity
- target type
- target identifier
- authoritative authorisation reference

An identifier alone is never sufficient authority.

## 4. Authorisation Boundary

Authority is established outside BOT-04.

BOT-04 must consume the established authority reference required by the
approved contract.

BOT-04 must reject a request when required authority is:

- missing
- invalid
- expired
- rejected
- otherwise insufficient

No deletion may occur after an authority failure.

## 5. Fleet Approval Boundary

Fleet and Contractor approval remain outside BOT-04.

Where Fleet architecture requires Contractor approval, BOT-04 may execute
only after the required upstream approval has been established.

BOT-04 must not:

- request approval itself
- decide approval
- replace Contractor authority
- bypass Fleet authority

## 6. Target Validation

The implementation must validate the deletion target before destructive
execution.

Malformed or unsupported targets must be rejected.

BOT-04 must not invent target mappings or deletion behaviour.

An undefined target behaviour requires:

> STOP — do not guess.

## 7. Deletion Semantics

Deletion semantics are determined by the authorised target/domain
contract.

The caller must not independently select destructive semantics through
arbitrary runtime flags.

The implementation must not expose unrestricted controls such as:

- hard_delete
- soft_delete
- purge
- tombstone

unless explicitly required by a future approved contract.

## 8. Cascade Boundary

The caller must not independently expand deletion scope.

Cascade behaviour must originate from the authorised target/domain
deletion contract.

BOT-04 must not invent additional targets.

## 9. Execution Boundary

BOT-04 executes only the authorised deletion operation.

It must not perform unrelated business operations as part of deletion.

The implementation must not become a universal cleanup or orchestration
engine.

## 10. Idempotency

The same authorised deletion request must be safely idempotent.

A retry must not cause repeated destructive effects.

If the target has already been authoritatively deleted, the implementation
may return an already-deleted result according to the approved result
contract.

Idempotency must never bypass authority validation.

## 11. Success Contract

BOT-04 may report deletion success only after authoritative deletion has
completed according to the applicable persistence contract.

It must not report success merely because:

- a request was accepted
- authority was valid
- a target existed
- an execution was started

## 12. Failure Contract

Failures must be explicit.

At minimum, the implementation must distinguish the relevant categories
required by the final public result contract, including:

- invalid request
- invalid target
- missing/invalid authority
- execution failure
- already-deleted/idempotent outcome

Exact public error identifiers must be finalised before implementation
if not already defined by architecture.

If an error category is undefined and implementation depends on it:

> STOP — do not guess.

## 13. Atomicity Boundary

BOT-04 must respect the authoritative persistence layer's transaction
and atomicity guarantees.

The implementation must not claim distributed rollback across independent
systems unless the architecture explicitly provides that guarantee.

A failed authoritative deletion must not be reported as successful.

## 14. Preservation Boundary

BOT-04 must respect domain-defined preservation requirements.

Protected historical or evidence records must not be silently destroyed.

Daily, weekly, and monthly presentation expiry is not deletion.

BOT-04 must not delete records merely because they leave a presentation
window.

## 15. Public API Boundary

Consumers must interact through the approved BOT-04 public contract.

Internal deletion mechanisms must remain implementation details.

Consumers must not depend directly on internal persistence or deletion
machinery.

## 16. Security Requirements

Deletion is a privileged destructive operation.

The implementation must ensure that invoking BOT-04 does not itself grant
authority.

No request may reach destructive execution without the required authority
context.

Malformed or unauthorised input must fail safely.

## 17. Testing Requirements

Tests must cover at minimum:

- authorised deletion
- missing authority
- invalid authority
- expired authority
- rejected authority
- malformed target
- unsupported target
- identifier-only request
- Fleet approval boundary
- caller-controlled deletion semantics
- caller-controlled cascade
- repeated authorised request
- already-deleted target
- successful deletion result
- execution failure
- preservation boundary
- presentation-expiry separation
- atomicity/failure behaviour
- public API boundary
- domain separation

## 18. Integration Test

At least one integration test must verify the complete BOT-04 boundary:

authorised request
→ target validation
→ deletion execution
→ authoritative result

The test must not introduce domain authority inside BOT-04.

## 19. Completion Gate

BOT-04 implementation is complete only when:

- implementation satisfies BLUEPRINT.md
- this contract is satisfied
- required unit tests pass
- integration tests pass
- public boundary is verified
- no unrelated responsibility exists
- README is completed
- profile is completed
- final repository checks pass

## 20. Repository Gate

Before final commit:

- inspect all BOT-04 files
- run required tests
- run `git diff --check`
- verify no unrelated files are included
- verify BOT-04 remains under the approved lifecycle/delete path

No intermediate per-file commit is required.

## 21. Final Stop Rule

If any implementation decision is not defined by the approved architecture,
Blueprint, or this Contract:

> STOP — do not guess.

Return to architecture before continuing.
