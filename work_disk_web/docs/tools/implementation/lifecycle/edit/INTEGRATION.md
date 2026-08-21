# BOT-07 — Edit ✏️ Integration Contract

## Caller
The caller supplies target identity, authority reference, explicit edit scope, new value, and expected lifecycle version.

## Domain ownership
The domain decides which fields are editable, validates domain values, and determines whether an Edited marker is user-visible.

## Original baseline
The domain/store must preserve the first authoritative pre-edit value as the immutable original baseline. BOT-07 never accepts a caller-supplied original.

## Current value
Every successful later edit replaces only the current value. Previous current values are not exposed as a revision timeline by BOT-07.

## Lifecycle interactions
Delete, Trash, and Archive remain separate lifecycle authorities. A stale edit cannot resurrect an item that has entered a terminal or incompatible lifecycle state.

## Notifications
BOT-07 does not send notifications. Callers may notify after the authoritative edit result.
