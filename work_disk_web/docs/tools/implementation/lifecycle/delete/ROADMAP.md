# Work_Disk Web — Tools — BOT-04
# Delete Bot — Implementation Roadmap

## 1. Architecture Baseline

- BLUEPRINT.md approved and preserved.
- All BOT-04 architectural invariants must remain intact.
- No implementation decision may silently override the Blueprint.

## 2. Implementation Contract

Create:

`IMPLEMENTATION_CONTRACT.md`

The contract must translate the Blueprint into precise implementation
requirements, including:

- deletion request boundary
- authoritative authorisation reference
- target validation
- deletion execution boundary
- deletion semantics boundary
- cascade boundary
- Fleet approval boundary
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

The implementation must remain limited to deletion execution.

It must not introduce:

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

- authorised deletion
- missing authority rejection
- invalid authority rejection
- expired/rejected authority handling
- malformed target rejection
- identifier-only request rejection
- Fleet approval boundary
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

- Blueprint remains unchanged unless an explicit architectural decision
  authorises a change.
- Implementation Contract is satisfied.
- Required tests pass.
- Integration tests pass.
- No unrelated responsibility exists in BOT-04.
- Working tree is clean apart from intended BOT-04 completion changes.
- Final architecture boundary is verified.

## 6. Completion Documentation

After implementation and tests are complete:

Create:

`README.md`

README must describe the completed BOT-04 implementation without becoming
a replacement for the Blueprint or Implementation Contract.

## 7. Profile

Create the BOT-04 profile only after implementation is complete.

The profile is the final identity and boundary record.

It must not introduce responsibilities that are absent from the approved
architecture.

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

BOT-04 documentation and implementation are committed together only after
the complete BOT-04 scope has passed its final verification.

Required final sequence:

1. `git add`
2. `git diff --cached --check`
3. `git commit`
4. `git push`
5. Verify clean working tree.
6. Verify local and remote HEAD.

No per-file commit is required during BOT-04 construction.

## 10. Stop Rule

At any point, if implementation encounters an undefined architectural
decision:

> STOP — do not guess.

Return to architecture before continuing.

## 11. Final Success Condition

BOT-04 is complete only when:

- Blueprint is preserved.
- Implementation Contract is satisfied.
- Implementation is complete.
- Required tests pass.
- Integration boundary passes.
- README is complete.
- Profile is complete.
- No unrelated responsibility has entered BOT-04.
- Final commit is created.
- Changes are successfully pushed.
