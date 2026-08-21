# BOT-08 — Search 🔎 Implementation Contract

## Command
`SearchCommand` carries request identity, an opaque authority reference, an opaque searchable-scope reference, target type, generic search mode, query and/or criteria, finite result limit, and opaque pagination cursor.

## Authority
The caller/domain supplies `SearchAuthority`. BOT-08 invokes it before any provider execution. BOT-08 never manufactures permission.

## Provider
The caller/domain supplies `SearchProvider`. The provider owns storage/index access, matching semantics, lifecycle visibility, consistency/freshness guarantees, projection policy, ranking, and cursor semantics.

## Result
Explicit result codes are `Results`, `Empty`, `AuthorityRejected`, `InvalidRequest`, `InvalidScope`, and `ExecutionFailed`.

## Isolation
The searchable scope is mandatory and opaque. BOT-08 must not infer account/role ownership from target type, field names, or page names.

## Projection
`SearchHit` exposes only opaque target type/id references plus provider ranking. Domain payload projection is outside BOT-08.

## Read-only invariant
BOT-08 has no mutation boundary and must never edit, delete, archive, trash, or otherwise alter searched state.

## Hardcoding prohibition
No page name, domain entity, field, permission rule, lifecycle policy, notification rule, ownership rule, or result presentation is hardcoded into BOT-08.

## Validation
A request requires request identity, authority reference, scope reference, target type, at least one query/criterion, and a non-zero finite limit.
