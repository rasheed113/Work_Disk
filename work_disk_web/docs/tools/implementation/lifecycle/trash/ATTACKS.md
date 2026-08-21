# BOT-05 — Trash 🗑️ Attack Register

## Attack 01 — Restore After Expiry
**Threat:** an expired item is restored because it still exists in Trash.

**Defence:** expiry is checked before restore and the store claim is atomic. Expired state cannot cross the restore boundary.

**Verdict:** PASS — no new law required.

## Attack 02 — Purge/Restore Race
**Threat:** restore and automatic purge race for the same item.

**Defence:** `TrashStore` provides an atomic lifecycle claim. Exactly one transition can claim the item; the losing operation receives a conflict.

**Verdict:** PASS.

## Attack 03 — Delete-One/Restore Race
**Threat:** a user restores an item while another request permanently destroys it.

**Defence:** the same atomic claim boundary governs both operations.

**Verdict:** PASS.

## Attack 04 — Duplicate Destruction
**Threat:** repeated Delete-One or purge calls permanently destroy the same item twice.

**Defence:** item lifecycle is durable and idempotent. A completed destruction cannot be claimed again.

**Verdict:** PASS.

## Attack 05 — Empty Trash Partial Success
**Threat:** the tool reports an empty Trash after only some items were destroyed.

**Defence:** `Emptied` is returned only when the authoritative store reports no remaining items in scope. Remaining items produce `PartiallyEmptied`.

**Verdict:** PASS.

## Attack 06 — Restore Payload Loss
**Threat:** the domain row is deleted before durable restoration material exists.

**Defence:** Trash intake requires a durable opaque payload reference. Delete/Trash integration must establish preservation before irreversible source destruction.

**Verdict:** PASS, subject to integration atomicity.

## Attack 07 — Restore Collision
**Threat:** the original target identity is now occupied by incompatible state.

**Defence:** BOT-05 does not invent conflict resolution. The authoritative restore boundary decides and reports failure/conflict; the Trash item remains retained on failure.

**Verdict:** PASS by bounded responsibility.

## Attack 08 — Fake Freshness
**Threat:** repeated calls or stale UI timestamps are treated as proof that a Trash item is current.

**Defence:** lifecycle state and expiry come from authoritative stored timestamps and injected policy/current-time input, not UI repetition.

**Verdict:** PASS.

## Attack 09 — Caller-Supplied Payload Injection
**Threat:** a restore caller replaces the preserved payload with arbitrary content.

**Defence:** restore consumes the stored `payloadReference`; caller input cannot substitute the payload.

**Verdict:** PASS.

## Attack 10 — Cross-Scope Empty Trash
**Threat:** Empty Trash accidentally destroys resources outside the authoritative Trash set.

**Defence:** Empty Trash enumerates only the authoritative Trash store and each destruction requires an item claim from that store.

**Verdict:** PASS.

## Attack 11 — Clock Boundary Manipulation
**Threat:** a caller supplies a false time to keep an item restorable or destroy it early.

**Defence:** production scheduling/current-time authority is outside BOT-05; the tool consumes trusted time and compares against stored expiry. Policy is injected.

**Verdict:** PASS by boundary separation.

## Attack 12 — Failed Destruction Becomes Silent Loss
**Threat:** destruction failure removes the Trash record even though the irreversible boundary failed.

**Defence:** completion is recorded only after successful destruction. Failure releases/retains the item for retry.

**Verdict:** PASS.

## Attack 13 — Retention Policy Confusion
**Threat:** implementation silently changes three calendar months into a fixed 90-day approximation.

**Defence:** retention is an injected policy boundary and the production policy is explicitly calendar-month based.

**Verdict:** PASS.

## Attack 14 — Evidence/Protected Data Overreach
**Threat:** Empty Trash or automatic purge destroys protected historical/evidence data that the domain has forbidden from destruction.

**Defence:** BOT-05 requires the authoritative destruction boundary to enforce domain preservation constraints. BOT-05 does not bypass those constraints.

**Verdict:** PASS by domain authority boundary.

## Attack 15 — Replayed Identifier
**Threat:** an old item ID is replayed after lifecycle completion.

**Defence:** the authoritative store returns current lifecycle state; identifier alone cannot recreate the item.

**Verdict:** PASS.

## Attack 16 — Scheduler Duplication
**Threat:** multiple purge workers process the same expired item.

**Defence:** atomic store claim makes purge idempotent and single-winner per item.

**Verdict:** PASS.

## Final Position

BOT-05 does not claim general-purpose self-healing or distributed transaction magic. Its authority-safe boundary is precise:

> **Trash may preserve recoverability; Trash may permanently destroy only an item that the authoritative Trash store has allowed it to claim.**
