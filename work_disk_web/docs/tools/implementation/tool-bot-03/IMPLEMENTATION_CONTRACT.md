# Work_Disk Web — Tools — TOOL-BOT-03
# Implementation Contract

## 1. Implementation Boundary

Implementation must use only:

- Approved Work_Disk architecture.
- TOOL-BOT-03 Blueprint.
- This Implementation Contract.

Do not import historical implementation assumptions.

## 2. Implementation Location

Source:

src/tools/tool-bot-03/

Tests:

tests/tools/tool-bot-03/

Documentation:

docs/tools/implementation/tool-bot-03/

Create only files required by the approved scope.

## 3. Generator Boundary

The generator owns identifier generation only.

It must not become an Account, Entry, Fleet, authentication, permission, or business-domain service.

## 4. Identifier Policies

The implementation must provide distinct policies for:

- Account ID
- Entry ID
- Fleet ID

The policies may share generation infrastructure but must not silently share incompatible authority rules.

## 5. Account ID Contract

Account IDs are exactly 9 characters long.

Account ID generation must not embed an online/offline generation mode.

Account ID generation uses the approved 62-character alphanumeric alphabet.

Account ID generation uses cryptographically secure randomness.

The final persistence operation must enforce uniqueness.

A race between concurrent requests must not permit duplicate Account IDs.

A detected collision must result in a new candidate or explicit failure.

## 6. Entry ID Contract

Entry IDs are exactly 11 characters long.

Entry IDs may be generated wherever the Tool is invoked; authority remains outside TOOL-BOT-03.

The identifier must use the approved 62-character alphanumeric representation.

The implementation must provide sufficient identifier space for very large Entry volumes.

Actual collision handling during authoritative persistence/synchronisation must remain detectable.

Rare accidental collision is an accepted property of the Entry ID model; silent undetected collision is not.

## 7. Fleet ID Contract

Fleet IDs are exactly 7 characters long.

Fleet IDs may be generated wherever the Tool is invoked; authority remains outside TOOL-BOT-03.

Fleet IDs use the approved 62-character alphanumeric representation.

Fleet IDs use the same generation mechanism as the other supported identifier classes.

Fleet creation, ownership, persistence, and authority remain outside TOOL-BOT-03.

## 8. Character and Length Rules

The approved character alphabet is:

A-Z + a-z + 0-9

Total alphabet size: 62 characters.

Special characters are excluded.

Identifier lengths are fixed by identifier class:

- Account ID: 9 characters
- Entry ID: 11 characters
- Fleet ID: 7 characters

A fixed `WD` prefix must not be added.

## 9. Randomness

The implementation must use a cryptographically secure random generation mechanism.

Do not use `std::rand()`, predictable counters, timestamps alone, process IDs, or other predictable values as the primary identifier-generation mechanism.

The generated value must be mapped into the approved 62-character alphabet without introducing invalid characters.

## 10. Generation / Authority Boundary

TOOL-BOT-03 does not implement a separate online/offline generation mode.

Generated identifiers are candidates. The Tool must not claim authoritative global uniqueness.

Authoritative persistence, synchronisation, collision handling, and domain authority are enforced by the appropriate external layer.

## 11. Validation

Generated identifiers must be validated before being returned.

Invalid generated output must never be exposed as a successful result.

## 12. Tests

Tests must cover at minimum:

- Account ID generation.
- Entry ID generation.
- Fleet ID generation.
- Format validation.
- Invalid requests.
- Repeated generation.
- Failure behaviour.
- Offline Entry generation.
- Collision detection behaviour.
- Concurrent Account ID uniqueness behaviour.
- Boundary separation between generator and domain logic.

## 13. Integration Test

At least one integration test must verify the Tool boundary from consumer request to generated identifier without creating unrelated domain authority inside the generator.

## 14. Decision Stop Rule

If implementation encounters an undefined architectural decision:

STOP.

Do not guess.

Do not copy historical code.

Record the missing decision and return to architecture.

## 15. Completion Gate

Completion requires:

- Approved Blueprint.
- Contract-compliant implementation.
- Passing tests.
- Passing integration test.
- No unrelated responsibilities.
- Completion record.
- Clean Git status.
- Successful Git push.
