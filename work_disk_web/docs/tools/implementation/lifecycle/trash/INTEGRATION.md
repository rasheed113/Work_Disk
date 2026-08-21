# BOT-05 — Trash 🗑️ Integration Contract

## Delete → Trash invariant

A user-facing delete that is intended to be recoverable MUST NOT irreversibly destroy the only copy of the resource before Trash has durable restoration material.

The integration boundary must therefore establish one of these authorised sequences:

1. **Atomic transfer:** the authoritative persistence transaction records the Trash entry and preserved payload before removing the active representation; or
2. **Durable preservation first:** Trash intake commits the preserved payload/reference before the authoritative deletion boundary removes the active representation, with a reconciliation contract for failure between the two systems.

BOT-05 itself does not pretend to provide a distributed transaction across independent stores.

## Delete Bot relationship

- Delete Bot decides/execut es the authorised deletion lifecycle according to its own contract.
- Trash Bot owns the post-delete recoverability lifecycle.
- Delete Bot must not silently claim `Deleted` for a recoverable deletion if the required Trash preservation contract has failed.
- The exact transaction coordinator belongs to the authoritative persistence/domain layer.

## Restore relationship

Restore is initiated through BOT-05 and delegated to the domain restore boundary. BOT-05 does not recreate domain state itself.

## Permanent destruction relationship

Permanent destruction from Trash is distinct from normal Delete Bot execution. BOT-05 calls only its destruction boundary for a validated Trash item.
