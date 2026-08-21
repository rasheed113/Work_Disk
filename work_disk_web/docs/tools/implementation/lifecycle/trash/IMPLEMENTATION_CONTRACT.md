# Work_Disk Web — Tools — BOT-05
# Trash 🗑️ Bot — Implementation Contract

## 1. Implementation Authority

Implementation follows the approved Work_Disk architecture, `BLUEPRINT.md`, and this contract. Undefined destructive behaviour is STOP — do not guess.

## 2. Public Request Model

`TrashEntry` contains:

- `itemId`
- `targetType`
- `targetId`
- `originalLocationReference`
- `payloadReference`
- `deletedAt`
- `expiresAt`

`TrashAuthority` contains a non-empty authority reference. BOT-05 treats the reference as an externally established authority proof; it does not interpret or manufacture authority.

## 3. Storage Boundary

`TrashStore` must provide durable operations for intake, lookup, atomic claim for restore, atomic claim for destruction, complete restore, complete destruction, release failed claim, and list of current items.

A production implementation must provide the durability/transaction guarantees required by the applicable Work_Disk persistence architecture. In-memory stores are test doubles only.

## 4. Retention Boundary

`TrashRetentionPolicy` calculates `expiresAt` from `deletedAt`. The production policy is configured for **3 calendar months**. The tool receives the policy by dependency injection; no `90 * 24h` shortcut and no hidden expiry constant is allowed in BOT-05 execution logic.

## 5. Restore Boundary

`TrashRestoreBoundary::restore(entry)` reconstructs the authoritative resource from the preserved payload reference. BOT-05 does not serialize or recreate domain objects itself.

On successful restore, BOT-05 completes the claimed trash transition. On failure, the item remains retained.

## 6. Destruction Boundary

`TrashDestructionBoundary::destroy(entry)` is the only irreversible destruction boundary used by BOT-05.

BOT-05 never deletes an arbitrary target directly. It only destroys a validated Trash item that was atomically claimed from the Trash store.

## 7. Operations

### Intake

1. Validate required identity, target and preservation references.
2. Calculate expiry through the retention policy.
3. Persist the item through `TrashStore`.
4. Report success only after durable intake succeeds.

### Restore

1. Validate authority and item identifier.
2. Lookup the item.
3. Reject if missing or expired.
4. Atomically claim for restore.
5. Call the restore boundary.
6. Complete the restore transition only after restore succeeds.
7. Release the claim on failure.

### Delete One

1. Validate authority and item identifier.
2. Atomically claim for destruction.
3. Call the destruction boundary.
4. Complete destruction only after the boundary succeeds.
5. Release the claim on failure.

### Empty Trash

1. Validate authority.
2. Obtain the current authoritative Trash set.
3. Attempt destruction of each item using atomic claims.
4. Complete each successful destruction.
5. Report `Emptied` only when no current items remain.
6. Report `PartiallyEmptied` when one or more items remain.

### Automatic Purge

1. The scheduler supplies trusted current time.
2. BOT-05 identifies expired items.
3. Expired items cannot be restored.
4. Each expired item is atomically claimed and destroyed.
5. Failed items remain in Trash for a later retry.
6. `NothingToPurge` means no expired item was eligible; it does **not** mean Trash is empty.
7. `Purged` means expired items were successfully removed and no items remain after the purge operation.
8. `PartiallyEmptied` means at least one eligible item or concurrent/current item remains.

## 8. Idempotency

Repeated lifecycle calls are resolved by the authoritative store state. A completed lifecycle cannot recreate an item merely because an old identifier is replayed. A production store may expose richer `AlreadyRestored`/`AlreadyDestroyed` states, but BOT-05 never treats a missing item as permission to recreate or destroy it.

## 9. Result Contract

`TrashOutcome` includes:

- `Stored`
- `Restored`
- `AlreadyRestored`
- `Destroyed`
- `AlreadyDestroyed`
- `NotFound`
- `Expired`
- `Emptied`
- `PartiallyEmptied`
- `Purged`
- `NothingToPurge`
- `Failed`

Failures distinguish invalid request, missing authority, storage failure, lifecycle conflict, restoration failure, destruction failure and retention-policy failure.

## 10. Security Invariants

- A UI button is not authority.
- An item ID is not authority.
- An expired item cannot be restored.
- A claimed item cannot be concurrently restored and destroyed.
- BOT-05 cannot expand an Empty Trash scope beyond the authoritative Trash store.
- Payload references cannot be replaced by caller-supplied arbitrary payloads during restore.
- Failed destruction does not remove the item from authoritative Trash state.

## 11. Tests

Tests must cover intake, policy injection, restore success/failure, restore-after-expiry, delete-one success/failure/idempotency, restore/destruction race claims, Empty Trash all-success, Empty Trash partial failure, purge with no eligible items, purge success, purge retry, invalid authority, invalid identifiers, and preservation-reference validation.

## 12. Completion Gate

BOT-05 is complete only when blueprint, attacks, roadmap, contract, README, profile, code and tests are consistent; no hidden policy constants exist; tests compile/pass; and repository changes are committed and pushed through the normal review workflow.
