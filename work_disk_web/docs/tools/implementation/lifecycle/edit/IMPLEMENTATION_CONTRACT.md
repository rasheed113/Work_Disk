# BOT-07 — Edit ✏️ Implementation Contract

## Command
`EditCommand` contains request identity, target identity/type, authority reference, edit scope, new value, expected lifecycle version, and a caller-provided presentation applicability flag for Edited state.

The command does not accept an `original_value` field. The original baseline is authoritative stored state, never caller input.

## Result
Explicit result codes: `Edited`, `NoOp`, `NotFound`, `AuthorityRejected`, `VersionConflict`, `InvalidRequest`, `LifecycleConflict`, `ExecutionFailed`.

## Original baseline invariant
On the first successful authoritative edit, the pre-edit value becomes the immutable original baseline. Later successful edits update current value only. Failed edits never replace the baseline.

## Revision history
BOT-07 does not expose a revision timeline or previous-value list. Internal provenance/audit records remain governed by the wider Work_Disk contracts.

## Edited marker
`edited_marker_applicable` is a presentation/domain signal, not authority. BOT-07 must not infer it from target type or hardcode domain names. The authoritative domain owns whether and how the marker is displayed.

## Authority
The caller/domain supplies an authority reference and implements `EditAuthority`. BOT-07 never manufactures permission.

## Concurrency and idempotency
A non-zero expected version is required. `EditStore::begin` claims the lifecycle transition and resolves already-completed/replayed requests. Stale versions must return `VersionConflict` or another explicit non-success outcome.

## Atomicity
Concrete store/executor implementations must provide the strongest atomic lifecycle guarantee available to the host. BOT-07 does not claim cross-system atomicity it cannot enforce.

## Hardcoding prohibition
No chat, inbox, comment, post, profile, fleet, entry, notification, field name, marker text, permission rule, cascade rule, or business policy is hardcoded in BOT-07.
