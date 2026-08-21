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

`TrashStore` must provide durable operations for:

- intake
- lookup
- atomic claim for restore
- atomic claim for destruction
- complete restore
- complete destruction
- release failed claim
- list current items

A production implementation must provide the durability/transaction guarantees required by the applicable Work_Disk persistence architecture. In-memory stores are test doubles only.

## 4. Retention Boundary

`TrashRetentionPolicy` calculates `expiresAt` from `deletedAt`. The production policy is configured for **3 calendar months**. The tool receives the policy by dependency injection; no `90 * 24h` shortcut and no hidden expiry constant is allowed in BOT-05 execution logic.

## 5. Restore Boundary

`TrashRestoreBoundary::restore(entry)` is responsible for reconstructing the authoritative resource from the preserved payload reference. BOT-05 does not serialize or recreate domain objects itself.

On successful restore, BOT-05 completes the claimed trash transition. On failure, the item remains retained.

## 6. Destruction Boundary

`TrashDestructionBoundary::destroy(entry)` is the only irreversible destruction boundary used by BOT-05.

BOT-05 never deletes an arbitrary target directly. It only destroys a validated trash item that was atomically claimed from the trash store.

## 7. Operations

### Intake

1. Validate required identity, target and preservation references.
2. Validate `deletedAt` and computed expiry.
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
2. Lookup the item.
3. Atomically claim for destruction.
4. Call the destruction boundary.
5. Complete destruction only after the boundary succeeds.
6. Release the claim on failure.

### Empty Trash

1. Validate authority.
2. Obtain the current authoritative trash set through the store boundary.
3. Attempt destruction of each item using atomic claims.
4. Complete each successful destruction.
5. Report `Emptied` only when the authoritative store contains no remaining trash items for the operation scope.
6. Report partial failure explicitly when one or more items remain.

### Automatic Purge

1. The scheduler supplies a trusted current time.
2. BOT-05 lists eligible expired items.
3. Expired items cannot be restored.
4. Each item is atomically claimed and destroyed.
5. Failed items remain in Trash for a later retry.

## 8. Idempotency

- Repeating intake with the same `itemId` must not create an ambiguous second lifecycle.
- Repeating restore after successful restore returns an explicit already-restored/not-found result according to the store state.
- Repeating delete-one after successful destruction returns an explicit already-destroyed/not-found result.
- Repeating Empty Trash when already empty is a successful no-op only if the caller is authorised.

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
- `Failed`

Failures must distinguish invalid request, missing authority, storage failure, lifecycle conflict, restoration failure and destruction failure.

## 10. Security Invariants

- A UI button is not authority.
- An item ID is not authority.
- An expired item cannot be restored.
- A claimed item cannot be concurrently restored and destroyed.
- BOT-05 cannot expand an Empty Trash scope beyond the authoritative trash store.
- Payload references cannot be replaced by caller-supplied arbitrary payloads during restore.
- Failed destruction does not remove the item from authoritative Trash state.

## 11. Tests

Tests must cover intake, three-month policy injection, restore success/failure, restore-after-expiry, delete-one success/failure/idempotency, restore/destruction race claims, Empty Trash all-success, Empty Trash partial failure, purge retry, invalid authority, invalid identifiers, and preservation-reference validation.

## 12. Completion Gate

BOT-05 is complete only when blueprint, attacks, roadmap, contract, README, profile, code and tests are consistent; no hidden policy constants exist; tests compile/pass; and repository changes are committed and pushed through the normal review workflow.
