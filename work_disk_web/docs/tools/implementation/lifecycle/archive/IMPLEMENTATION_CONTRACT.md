# BOT-06 Archive 📦 — Implementation Contract

## Public command
`ArchiveCommand` contains:
- `requestId`
- `operation` (`Archive` or `Unarchive`)
- `targetType`
- `targetId`
- `authorityReference`
- `sourceReference`
- `expectedVersion`

No domain-specific policy is encoded in the Tool Bot.

## Public result
Result is explicit and machine-readable:
- `Archived`
- `Unarchived`
- `AlreadyArchived`
- `AlreadyUnarchived`
- `NotFound`
- `AuthorityRejected`
- `VersionConflict`
- `InvalidRequest`
- `LifecycleConflict`
- `ExecutionFailed`

## Required interfaces
`ArchiveStore` owns durable lifecycle state. `ArchiveAuthority` validates caller authority. `ArchiveExecutor` performs the domain transition through an injected boundary. `ArchiveClock` supplies authoritative time only where the host contract requires it; BOT-06 has no built-in retention policy.

## Atomicity
The store/executor boundary must provide the strongest atomic transition available to the host. BOT-06 must not claim cross-system atomicity without an explicit host guarantee.

## Idempotency
`requestId` identifies one logical operation. Replays must return a compatible durable outcome and must not repeat a destructive or duplicate transition.

## Versioning
`expectedVersion` prevents stale callers from overwriting newer lifecycle state. A version conflict is explicit and non-success.

## Reference handling
`sourceReference` is opaque to BOT-06. The bot stores and passes it; it never parses it to invent a domain destination.

## No hardcoding
No inbox/chat/post/notification/fleet/document policy, retention period, permission rule, notification text, cascade rule, or UI semantics may be hardcoded here.

## Deferred build integration
CI/compiler integration is intentionally outside this bot implementation change and will be handled in the later build phase.
