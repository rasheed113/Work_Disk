# Work_Disk Web — Tools — BOT-04
# Delete Bot — Architecture Blueprint

## 1. Purpose & Scope

BOT-04 is the Delete Bot.

BOT-04 provides a single, strictly bounded deletion execution boundary
for Work_Disk.

BOT-04 executes deletion only when the required upstream authority has
already been established.

The governing principle is:

> Authority decides. Delete Bot executes.

BOT-04 does not decide whether a resource should be deleted.

BOT-04 is not an Archive Bot, Trash Manager, Restore Handler, Filter,
Sort, universal cleanup/orchestration component, or domain approval engine.

## 2. Core Invariants

The following rules are non-negotiable:

- BOT-04 only executes authorised deletion.
- Authority remains outside BOT-04.
- BOT-04 does not perform ownership or permission decisions.
- Callers cannot select arbitrary deletion semantics.
- Callers cannot independently expand cascade scope.
- Fleet warning/approval logic remains outside BOT-04 in a separate
  Fleet-specific architectural boundary.
- Missing or invalid authority means no deletion.
- The same authorised deletion request must be safely idempotent.
- BOT-04 must not report successful deletion before authoritative
  deletion has completed.
- Presentation expiry is never interpreted as deletion.
- Protected historical or evidence data cannot be silently destroyed.
- Archive, Trash, and Restore are outside BOT-04.
- UI behaviour is outside BOT-04.
- Domain business logic is outside BOT-04.
- BOT-04 must not become a universal cleanup or orchestration engine.
- Undefined destructive behaviour requires STOP; BOT-04 must not guess.

## 3. Authority Boundary

The relevant domain or upstream authority determines whether deletion
is permitted.

BOT-04 receives an authorised deletion operation only after the required
authority has been established.

BOT-04 must not:

- invent authority
- grant authority
- bypass authority
- weaken approval requirements
- replace domain authority
- perform ownership decisions
- perform permission decisions

## 4. Fleet Separation Boundary

BOT-04 is deliberately generic and contains no Fleet-specific approval
workflow.

If Fleet architecture requires Contractor approval before a Fleet entry
can be deleted, that warning/approval decision must be established by a
separate Fleet-specific architectural boundary before BOT-04 receives an
authorised deletion operation.

BOT-04 does not request, evaluate, approve, reject, or store Fleet
Contractor approval semantics.

The separate Fleet approval component may call BOT-04 only after the
required approval outcome has become authoritative.

## 5. Conceptual Input Contract

The deletion operation requires, at minimum:

- A unique request identifier.
- A target type.
- A target identifier.
- An authoritative authorisation reference.

Conceptual shape:

    {
      "request_id": "uuid-v4",
      "target_type": "string_entity_identifier",
      "target_id": "string_or_number_identifier",
      "authorisation_reference": "string_reference"
    }

The exact representation of authority evidence is an implementation
contract decision.

BOT-04 must not assume that authority evidence must use one specific
technical mechanism unless separately authorised.

Approval workflows are not part of the generic Delete Bot request.

## 6. No Caller-Controlled Deletion Semantics

The caller must not arbitrarily select destructive behaviour through
raw flags such as:

- hard_delete
- soft_delete
- purge
- tombstone

Deletion semantics are determined by the authorised target/domain
delection contract.

BOT-04 executes the semantics that have been authorised.

## 7. No Caller-Controlled Cascade

The caller must not independently expand deletion scope through an
arbitrary cascade flag.

Any cascading behaviour must be defined by the authorised target/domain
deletion contract.

BOT-04 must not invent additional deletion targets.

## 8. Deletion Execution

BOT-04 executes only the deletion operation contained within the
authorised scope.

An identifier by itself is never sufficient authority for destructive
action.

BOT-04 must not perform unrelated domain operations as a side effect of
receiving a deletion request.

## 9. Idempotency

Retrying the same authorised deletion request must be safely idempotent.

A repeated request must not cause repeated destructive effects.

Where the target has already been authoritatively deleted, the operation
may return an appropriate already-deleted result according to the public
result contract.

Idempotency must not weaken the authority requirement.

## 10. Success Guarantee

BOT-04 must not report successful deletion unless the authoritative
deletion operation has completed according to the applicable persistence
contract.

A request that fails before authoritative completion must not be reported
as successfully deleted.

## 11. Failure & Safety

Malformed targets must be rejected.

Missing, invalid, expired, or rejected authority must result in no
deletion.

If the authorised deletion cannot be completed, BOT-04 must return an
explicit failure according to its result contract.

BOT-04 must not silently convert an execution failure into success.

Undefined destructive behaviour requires:

> STOP — do not guess.

## 12. Atomicity Boundary

BOT-04 must respect the atomicity guarantees of the authoritative
persistence layer.

It must not claim a universal distributed rollback guarantee across
independent physical systems unless such a guarantee is explicitly
provided by the applicable architecture.

The authoritative deletion result is the basis for reporting success.

## 13. Preservation Boundary

BOT-04 must respect preservation requirements established by the
authoritative domain architecture.

Protected historical or evidence records must not be silently destroyed.

Daily, weekly, and monthly presentation-window expiry does not constitute
deletion.

Presentation cleanup or projection reset is outside BOT-04.

## 14. Domain Separation

BOT-04 does not own:

- Account authority
- Identity authority
- Fleet authority
- Contractor authority
- Social ownership
- Privacy authority
- Authentication
- Permissions
- Business-domain rules
- Fleet warning/approval workflows
- Presentation lifecycle
- Archive lifecycle
- Trash lifecycle
- Restore lifecycle

## 15. Explicit Non-Responsibilities

BOT-04 does not:

- decide whether deletion is permitted
- check user ownership
- perform permission evaluation
- manage UI confirmation
- manage Fleet warnings
- manage Contractor approval
- manage Archive
- manage Trash
- manage Restore
- interpret presentation expiry as deletion
- invent cascade behaviour
- dispatch unrelated notifications
- become a universal cleanup engine
- become a general orchestration engine

## 16. Security Boundary

Deletion is a privileged destructive operation.

Calling BOT-04 does not grant deletion authority.

BOT-04 executes established authority; it does not establish authority.

The deletion boundary must reject requests that cannot demonstrate the
required upstream authority.

## 17. Architectural Boundary

BOT-04 is a Delete Bot only.

Its responsibility ends at authorised deletion execution and its directly
required execution result.

Any capability outside this boundary requires a separate architectural
decision and must not be silently added to BOT-04.

## 18. Principle

BOT-04 follows one fundamental rule:

> Delete only what the authorised domain has permitted to be deleted.

Domain authority decides.

BOT-04 executes.
