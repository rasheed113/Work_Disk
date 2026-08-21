# BOT-07 — Edit ✏️ Blueprint

## Purpose
BOT-07 is a generic multi-caller lifecycle Tool Bot for authorised mutation of an existing target's current user-visible/domain value.

## Locked semantics
- Edit changes the current authoritative value.
- The first authoritative pre-edit value is the immutable user-visible original baseline.
- Repeated edits never replace that baseline.
- No user-facing revision-history timeline is produced by BOT-07.
- `Edited` is applicable only where the caller/domain presentation contract requires it.
- Internal provenance/audit evidence remains subject to the wider architecture; absence of revision-history UI does not permit evidence destruction.

## Boundary
Caller/domain owns:
- permission and authority policy
- target semantics
- field/domain validation
- whether an edit is permitted
- whether an Edited marker is user-visible
- presentation and notification

BOT-07 owns:
- request validation at its generic boundary
- authority invocation
- lifecycle claim/idempotency boundary
- execution orchestration
- explicit result reporting

## Non-goals
BOT-07 does not own Delete, Trash, Archive, Search, Mark/selection, notifications, permissions, cascade policy, or domain-specific business rules.

## Concurrency
Expected lifecycle version is mandatory. Stale concurrent edits resolve as explicit version conflicts rather than silently overwriting newer authoritative state.

## Recovery
Retry of the same logical request must resolve through the durable lifecycle boundary. A failed mutation must not create a new original baseline.
