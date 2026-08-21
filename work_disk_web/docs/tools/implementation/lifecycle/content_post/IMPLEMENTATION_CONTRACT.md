# BOT-13 — Content/Post Implementation Contract

## Command
`ContentCommand` carries request identity, opaque authority reference, opaque creation-scope reference, content kind, opaque payload reference, opaque visibility-policy reference, and caller-provided idempotency key.

## Authority
The caller/domain supplies `ContentAuthority`. BOT-13 invokes it before provider execution and never manufactures permission.

## Provider
The caller/domain supplies `ContentProvider`. The provider owns persistence, identifier generation, lifecycle/versioning, idempotency resolution, visibility enforcement, and domain-specific content semantics.

## Result
Explicit result codes: `Created`, `InvalidRequest`, `AuthorityRejected`, `ScopeRejected`, `Conflict`, and `ExecutionFailed`.

## Isolation
Creation scope is mandatory and opaque. BOT-13 must not infer account, role, relationship, or ownership from target types, field names, page names, or UI context.

## Read boundary
BOT-13 creates content only. It does not edit existing content, distribute it to feeds, react, comment, notify, acquire media, or rank content.

## Identifier boundary
BOT-13 does not generate or decide identifier format/uniqueness. The authoritative provider/domain owns content identity.

## Replay
An idempotency key is mandatory. Concrete providers must resolve replay according to the wider Work_Disk idempotency laws.

## Hardcoding prohibition
No account, profile, feed, chat, comment, media, notification, permission rule, visibility rule, or presentation string is hardcoded into BOT-13.
