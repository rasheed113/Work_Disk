# Work_Disk Web — Tools — TOOL-BOT-01
# ID Generator Blueprint

## 1. Purpose

TOOL-BOT-01 provides reusable identifier generation for Work_Disk.

It is a shared Tool capability, not a domain authority.

## 2. Supported Identifier Classes

The initial approved identifier classes are:

- Account ID
- Entry ID
- Fleet ID

No additional identifier class may be introduced by implementation without an architectural decision.

## 3. Account ID

Account creation is an online operation.

Account IDs are exactly 9 characters long.

Account IDs use the shared alphanumeric character set defined by this Blueprint.

Account ID generation must not embed an online/offline generation mode.

Account ID uniqueness is authoritative.

The authoritative persistence layer must reject duplicate Account IDs.

The generator must safely handle an attempted collision by generating another candidate.

Account ID generation must not require offline device coordination.

## 4. Entry ID

Entry IDs may be generated wherever the Tool is invoked; authority remains outside TOOL-BOT-01.

Entry IDs are exactly 11 characters long.

Entry IDs use the shared alphanumeric character set defined by this Blueprint.

Entry IDs must remain compact enough for normal UI display.

The identifier space is intentionally large so that accidental collisions are extremely unlikely.

Entry IDs do not use the same strict global uniqueness model as Account IDs.

When Entries are synchronised or persisted authoritatively, an actual collision must remain detectable.

## 5. Fleet ID

Fleet IDs may be generated wherever the Tool is invoked; authority is determined outside the generator.

Fleet IDs are exactly 7 characters long.

Fleet IDs use the shared alphanumeric character set defined by this Blueprint.

Fleet IDs use the same generation mechanism as the other supported identifier classes.

Fleet-specific creation and authority remain outside the generator.

The generator must not create or mutate Fleet records.

## 6. Character Set

Generated IDs use the full alphanumeric character set:

- A-Z
- a-z
- 0-9

This provides 62 possible characters per position.

Special characters are not included.

A fixed `WD` prefix is not required.

The identifier itself therefore contains the complete generated value without a mandatory product prefix.

## 7. Generation Algorithm

The generator uses a cryptographically secure random number generation mechanism.

Ordinary predictable pseudo-random generation such as `std::rand()` must not be used.

The generated random value is mapped to the approved 62-character alphanumeric alphabet.

The generator must validate the resulting identifier before returning it.

## 8. Authority Boundary

The ID Generator:

- Generates identifiers.
- Validates generator input.
- Applies identifier-class policy.
- Reports generation failure.

It must not:

- Create Account records.
- Create Entry records.
- Create Fleet records.
- Decide ownership.
- Decide permissions.
- Authenticate users.
- Perform unrelated database business operations.

## 9. Generation and Authority Separation

TOOL-BOT-01 generates identifier candidates only.

The generator does not select, encode, or enforce an online/offline generation mode.

Authoritative uniqueness, persistence, synchronisation, and domain authority remain outside TOOL-BOT-01.

## 10. Collision Principle

Account ID collision must be authoritatively rejected by persistence.

Entry ID collision is treated as an exceptional condition and must be detectable during synchronisation or authoritative persistence.

The generator must never silently claim that an identifier is globally unique when global authority is unavailable.

## 11. Failure Principle

Generation failures must be explicit.

The implementation must not silently return an empty, malformed, or invalid identifier.

## 12. Security Principle

Identifiers are identifiers, not secrets.

Sensitive information must never be encoded into an identifier.

## 13. Consumer Principle

Consumers request identifiers through the Tool boundary.

Consumers must not depend on the generator's internal algorithm.

## 14. Completion Gate

TOOL-BOT-01 is complete only when:

- Blueprint is approved.
- Implementation Contract is satisfied.
- Required unit tests pass.
- Required integration tests pass.
- Identifier boundaries are respected.
- No unrelated domain logic is embedded.
- Completion record exists.
- Git working tree is clean.
- Changes are pushed to the authoritative repository.
