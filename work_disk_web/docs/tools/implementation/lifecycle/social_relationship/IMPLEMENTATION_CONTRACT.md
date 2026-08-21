# BOT-14 — Social Relationship Implementation Contract

## Command
`RelationshipCommand` carries request identity, opaque authority and relationship-scope references, actor and subject references, a bounded relationship operation, idempotency key, and expected version.

## Authority
The caller/domain supplies `RelationshipAuthority`; BOT-14 invokes it before provider execution.

## Provider
The provider owns relationship persistence, lifecycle transitions, versioning, deduplication, relationship policy, and relationship identifiers.

## Operations
Follow, Unfollow, RequestConnection, AcceptConnection, RejectConnection.

## Explicit separation
Block, mute, report, recommendation, feed ranking, notification delivery, messaging, and moderation are not implemented by BOT-14.

## Concurrency
Expected version and idempotency key are mandatory inputs. Concrete providers must implement the wider Work_Disk CAS/replay laws.

## Hardcoding prohibition
No account type, role, page, feed, notification rule, or UI behavior is hardcoded into BOT-14.
