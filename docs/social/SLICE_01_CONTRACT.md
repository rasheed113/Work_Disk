# Social Vertical Slice 01 — Contract

**Status:** Implementation target

## Goal

Prove a real end-to-end social action without fake or hardcoded domain data.

## Flow

`Authenticated Identity → Home Read → Create Post → Persist Post → Home Read-back → Like → Activity`

## Rules

- Identity comes from the authentication boundary.
- A post must contain a real authenticated author ID.
- Post content comes from the user's submitted input.
- Persistence must write to the authoritative datastore.
- Home must read persisted records through the application boundary.
- A like is identified by `(postId, actorId)` and is idempotent.
- Activity is generated from the authoritative like action.
- UI must not fabricate success or counts.
- Provider-specific APIs are isolated behind infrastructure ports.
- No seed/demo records are required for correctness.
- An empty feed is a valid state when no persisted posts exist.

## Acceptance evidence

A slice is complete only when a test or deployed verification can demonstrate:

1. an authenticated identity is resolved;
2. that identity creates a post;
3. the post receives a persistent identifier;
4. a fresh Home read returns that same post;
5. the identity likes that post;
6. a fresh activity read contains the resulting activity event.
