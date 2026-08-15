# TOOL-BOT-01 — ID Generator

Work_Disk Web shared identifier-generation Tool.

## Approved Identifier Classes

- Account ID — 9 characters
- Entry ID — 11 characters
- Fleet ID — 7 characters

## Character Set

All identifiers use:

- A-Z
- a-z
- 0-9

Total: 62 characters.

Special characters are excluded.

A fixed `WD` prefix is not used.

## Generation Algorithm

Cryptographically secure random generation.

## Authority

Account IDs:

- Generation mode is not encoded in TOOL-BOT-01.
- Authoritative uniqueness.
- Duplicate Account IDs must never be accepted.

Entry IDs:

- Generation may be invoked in any permitted execution context.
- Compact.
- Rare collision is acceptable.
- Collision must remain detectable when authoritative persistence/synchronisation is available.

Fleet IDs:

- Generation may be invoked in any permitted execution context.
- Compact.
- Same identifier-generation mechanism as the other supported classes.

## Boundary

The Tool generates identifiers.

It does not create, own, authenticate, authorise, delete, or otherwise manage the entities represented by those identifiers.

## Status

Architecture / Contract preparation complete.

Implementation has not started.
