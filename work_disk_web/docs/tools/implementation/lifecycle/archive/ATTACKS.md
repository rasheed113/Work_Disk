# BOT-06 Archive 📦 — Attack Register

Status: attacks resolved at blueprint level; implementation must preserve these invariants.

| # | Attack | Resolution |
|---|---|---|
| 06A | Archive mistaken for Delete | Separate lifecycle states; archive never invokes destruction. |
| 06B | Archive mistaken for Trash | Trash retention/destruction remains BOT-05; archive has no automatic destruction. |
| 06C | Caller without authority invokes Archive | Reject without authoritative authority context. |
| 06D | UI button becomes authority | UI identifiers are presentation only; authority comes from caller context. |
| 06E | Cross-domain payload coupling | Use opaque target/source references; BOT-06 stays domain-neutral. |
| 06F | Duplicate archive request | Stable request identity + idempotent result. |
| 06G | Double unarchive | Lifecycle/version check prevents duplicate restoration. |
| 06H | Archive/unarchive race | Versioned/atomic transition boundary; stale transition rejected. |
| 06I | Crash after archive persistence before response | Retry observes durable state and returns the same lifecycle result. |
| 06J | Crash after unarchive | Durable transition state prevents duplicate restoration. |
| 06K | Lost source/original-location reference | Archive requires durable opaque reference; missing reference blocks unarchive rather than inventing a destination. |
| 06L | Concurrent callers archive same target | Deterministic lifecycle claim; one transition wins, others observe compatible idempotent state or conflict. |
| 06M | Archive of already deleted/trashed target | Cross-lifecycle conflict is rejected; BOT-06 cannot resurrect or reinterpret deletion. |
| 06N | Delete requested after archive | Delete remains domain-authorised; archive does not shield an item from lawful deletion. |
| 06O | Unarchive after domain authority revoked | Revalidate authority at execution boundary; stale permission cannot restore access. |
| 06P | Partial external/domain transition | Do not report success without authoritative completion; explicit failure/reconciliation result. |
| 06Q | Malicious/malformed target reference | Validate structure and authority binding; opaque reference prevents payload interpretation as policy. |
| 06R | Replay of old archive/unarchive command | Request identity + lifecycle version/authority context rejects stale replay. |
| 06S | Archive used to bypass visibility/privacy policy | BOT-06 does not grant visibility; domain projection remains authoritative. |
| 06T | Archive used as retention/destruction engine | No automatic expiry or permanent destruction semantics inside BOT-06. |
| 06U | Multi-domain state collision | Domain-specific state is not overwritten; only archive lifecycle metadata changes through declared boundary. |
| 06V | Recovery from stale snapshot | Historical snapshot cannot manufacture current archive/unarchive authority. |
| 06W | Replicated archive divergence | Canonical domain lineage determines state; local replica popularity/arrival does not. |
| 06X | Notification says archived before commit | Notification is outside BOT-06; callers must publish only after authoritative result. |
| 06Y | Empty/missing target | Explicit NOT_FOUND/INVALID outcome; no guessed resource. |
| 06Z | Undefined cascade archive | No implicit child/cascade behaviour; caller must explicitly provide authorised operation semantics. |

## Final invariants
1. Archive is preservation, not destruction.
2. Authority comes from the caller/domain boundary, not BOT-06.
3. A valid request cannot expand target scope.
4. Stale/replayed lifecycle operations cannot overwrite newer authoritative state.
5. Failure never becomes success through ambiguity.
6. Historical evidence is not silently destroyed.
7. Domain policy remains outside the generic Tool Bot.
