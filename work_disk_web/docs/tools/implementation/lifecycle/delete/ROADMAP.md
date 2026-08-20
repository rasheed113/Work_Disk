# Work_Disk Web — Tools — BOT-04
# Delete Bot — Implementation Roadmap

## 1. Architecture Baseline

- BLUEPRINT.md approved and preserved.
- BOT-04 is the generic deletion execution boundary.
- Fleet warning/Contractor approval is explicitly outside BOT-04.
- A separate Fleet-specific logical board will own Fleet deletion warning,
  approval, rejection, and related workflow decisions.
- No implementation decision may silently override the Blueprint.

## 2. Implementation Contract

`IMPLEMENTATION_CONTRACT.md` translates the Blueprint into precise
implementation requirements, including:

- deletion request boundary
- authoritative authorisation reference
- target validation
- deletion execution boundary
- deletion semantics boundary
- cascade boundary
- Fleet separation boundary
- idempotency
- failure handling
- atomicity boundary
- result/error contract
- security requirements
- test requirements

If an implementation requirement is not defined by the Blueprint:

> STOP — do not guess.

## 3. Implementation

Implementation must follow only:

1. Approved Work_Disk architecture
2. BOT-04 BLUEPRINT.md
3. BOT-04 IMPLEMENTATION_CONTRACT.md

The implementation must remain limited to generic deletion execution.

It must not introduce:

- Fleet warning/approval workflow
- Archive
- Trash
- Restore
- Filtering
- Sorting
- UI behaviour
- Domain ownership logic
- Permission systems
- Universal cleanup orchestration
- Unauthorised cascade logic

## 4. Testing

Tests must verify at minimum:

- authorised generic deletion
- missing authority rejection
- invalid authority rejection
- expired/rejected authority handling
- malformed target rejection
- identifier-only request rejection
- generic deletion without Fleet approval fields
- Fleet approval separation boundary
- caller-controlled mode rejection
- caller-controlled cascade rejection
- idempotent retry behaviour
- successful deletion result
- failed deletion result
- preservation boundary
- presentation-expiry separation
- atomicity/failure behaviour
- domain-boundary separation

## 5. Completion Verification

Before documentation completion:

- Blueprint remains aligned with the approved generic Delete Bot boundary.
- Implementation Contract is satisfied.
- Required tests pass.
- Integration tests pass.
- No unrelated responsibility exists in BOT-04.
- Working tree is clean apart from intended BOT-04 completion changes.
- Final architecture boundary is verified.

## 6. Completion Documentation

README and PROFILE describe the completed generic Delete Bot without
becoming replacements for the Blueprint or Implementation Contract.

## 7. Separate Fleet Board

Fleet-specific warning/approval is intentionally deferred to a separate
logical board.

That future board will define, at its own architectural boundary:

- Fleet entry deletion warning
- Contractor account confirmation
- approval/rejection outcomes
- cancellation on rejection
- authority hand-off to BOT-04 after approval

No Fleet approval logic is implemented in BOT-04.

## 8. Final Repository Gate

Before committing:

- Review all BOT-04 files.
- Run repository checks.
- Run `git diff --check`.
- Verify no accidental files are included.
- Verify no unrelated architecture has been introduced.
- Verify BOT-04 remains under:

`docs/tools/implementation/lifecycle/delete/`

## 9. Git Completion

BOT-04 is complete only after implementation and tests pass.

The repository publication sequence is:

1. inspect intended changes
2. verify tests
3. verify diff/checks
4. commit the complete BOT-04 scope
5. push the authorised branch
6. verify remote state

## 10. Stop Rule

At any point, if implementation encounters an undefined architectural
decision:

> STOP — do not guess.

Return to architecture before continuing.

## 11. Final Success Condition

BOT-04 is complete only when:

- Blueprint is satisfied.
- Implementation Contract is satisfied.
- Generic Delete Bot implementation is complete.
- Required tests pass.
- Integration boundary passes.
- README is complete.
- Profile is complete.
- No Fleet approval workflow has entered BOT-04.
- No unrelated responsibility has entered BOT-04.
