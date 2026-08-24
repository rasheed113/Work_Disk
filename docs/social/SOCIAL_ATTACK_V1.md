# Work_Disk Social Attack v1

**Status:** Completed against Social Architecture v1.

## Purpose

Attempt to break the architecture before implementation. Any failure found here becomes an architecture change, not a code patch.

## Attack 1 — Dashboard leakage

**Attack:** Make Social Home depend on Dashboard state, Dashboard settings, or Dashboard page properties.

**Result:** Rejected.

**Invariant:** Dashboard is a navigation destination only and remains outside the Social domain.

## Attack 2 — Page property dumping

**Attack:** Put Home, Post, Video, Profile, Inbox, and Activity properties into one global page registry that owns their behaviour.

**Result:** Rejected.

**Invariant:** Each page owns its own properties and functions. Shared infrastructure may exist, but page ownership remains local.

## Attack 3 — Firebase becomes the domain

**Attack:** Model Social entities directly as Firebase SDK objects and let provider schemas define business rules.

**Result:** Rejected.

**Invariant:** Firebase is infrastructure behind ports/adapters. Social contracts define domain meaning.

## Attack 4 — Fake feed

**Attack:** Render hard-coded posts so the UI appears complete before persistence exists.

**Result:** Rejected.

**Invariant:** Production-visible content must originate from an authoritative data path. Empty state is valid; fake records are not.

## Attack 5 — Client authorization

**Attack:** Trust React state, hidden buttons, route parameters, or local storage as proof that a user may read/write data.

**Result:** Rejected.

**Invariant:** Authorization is enforced by authenticated identity plus domain relationship/context and provider security rules.

## Attack 6 — Activity becomes source of truth

**Attack:** Reconstruct likes/comments/shares/posts from notification/activity records.

**Result:** Rejected.

**Invariant:** Activity points to authoritative actions/objects. Activity is not the source of truth for domain state.

## Attack 7 — Conversation privacy bypass

**Attack:** Allow a client to subscribe to a conversation by knowing its ID.

**Result:** Rejected.

**Invariant:** Conversation reads and realtime subscriptions require participant authorization.

## Attack 8 — Media/path leakage

**Attack:** Store arbitrary device file paths in domain records and treat them as permanent media identity.

**Result:** Rejected.

**Invariant:** Domain stores provider-neutral media references and lifecycle metadata.

## Attack 9 — Realtime becomes authoritative

**Attack:** Treat a WebSocket/Firebase realtime event as proof that a transaction succeeded.

**Result:** Rejected.

**Invariant:** Domain persistence/state transition is authoritative; realtime is delivery/observation infrastructure.

## Attack 10 — Navigation growth by accident

**Attack:** Add arbitrary buttons to bottom navigation whenever a new feature appears.

**Result:** Rejected.

**Invariant:** v1 has exactly Home, Post, Video, Profile. Navigation changes require an architecture revision.

## Attack 11 — Account/profile scope collision

**Attack:** Turn Social Profile into a catch-all account/settings object.

**Result:** Rejected.

**Invariant:** Social Profile owns its Social-facing profile experience only.

## Attack 12 — Deleted content resurrection

**Attack:** Serve stale cached/read-model content after authoritative deletion.

**Result:** Rejected.

**Invariant:** Deletion/revocation must invalidate or suppress dependent read models according to explicit lifecycle contracts.

## Attack 13 — Cross-user data leakage

**Attack:** Query collections broadly and filter in the browser.

**Result:** Rejected.

**Invariant:** Access boundaries are enforced before data reaches the client.

## Attack 14 — Provider lock-in

**Attack:** Import Firebase SDK types throughout domain/application modules.

**Result:** Rejected.

**Invariant:** Provider-specific types terminate at infrastructure adapters.

## Attack 15 — Partial product illusion

**Attack:** Build separate screens with no complete real journey between them.

**Result:** Rejected.

**Invariant:** First implementation must prove one complete real Social journey end-to-end.

## Attack conclusion

No architecture-breaking contradiction was accepted. The architecture survives the current attack set.

**Next gate:** Boundary v1.
