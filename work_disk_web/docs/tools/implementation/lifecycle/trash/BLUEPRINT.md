# Work_Disk Web — Tools — BOT-05
# Trash 🗑️ Bot — Architecture Blueprint

## 1. Purpose

BOT-05 owns the Trash lifecycle for deleted resources. It preserves a durable restore reference for deleted content, exposes restore and permanent-destruction operations, and purges items after the authoritative retention period.

The user-facing retention rule is **3 calendar months**. The retention policy is supplied through an injected policy boundary; BOT-05 does not hide policy constants inside execution logic.

## 2. Core Lifecycle

```text
Authorised Delete
      ↓
Trash intake 🗑️
      ↓
Trash item retained
      ├── Restore ↩️
      ├── Delete one 🗑️ → permanent destruction
      ├── Empty Trash 🗑️ → permanent destruction of all current items
      └── retention reached → automatic permanent destruction
```

Automatic purge is scheduler-driven: a scheduler calls BOT-05; BOT-05 decides eligibility and executes the defined destruction boundary. BOT-05 does not invent a scheduler.

## 3. Authority Rules

- A caller must provide established authority for restore or permanent-destruction operations.
- BOT-05 does not grant authority, choose approvers, or implement approval policy.
- Trash visibility is not proof of ownership or permission.
- A valid item identifier cannot bypass authority or lifecycle checks.

## 4. Preservation Rule

A trash item must retain enough durable information to restore the resource through an authoritative restore boundary. BOT-05 therefore stores an opaque `payloadReference` rather than assuming domain-specific object formats.

Delete and Trash integration must ensure that the restore material is durably captured before the source representation is irreversibly destroyed. BOT-05 must never claim successful trash intake if the required preservation reference was not accepted by its storage boundary.

## 5. Retention Rule

Each item has an authoritative `expiresAt`. The retention policy determines that timestamp when the item enters Trash.

- Retention is measured as a calendar-month policy, not an assumed fixed 90-day interval.
- Before expiry, restore remains eligible unless another authoritative lifecycle rule blocks it.
- At or after expiry, restore is not eligible and permanent destruction becomes eligible.
- A failed destruction keeps the item retained and observable; the system must not falsely report successful purge.

## 6. Restore Semantics

Restore is a lifecycle transition, not a new resource creation request.

The restore boundary receives the original target identity, original location reference, and preserved payload reference. BOT-05 does not decide domain-specific conflict resolution.

If restoration fails, the trash item remains retained unless the authoritative storage contract reports a completed restore.

## 7. Permanent Destruction

`DeleteOne` permanently destroys one trash item after authority and lifecycle validation.

`EmptyTrash` attempts permanent destruction of every item visible in the authoritative trash store at the operation boundary. Success means the operation has established that no current trash items remain. Partial failure is reported explicitly; failed items remain retained.

Permanent destruction is irreversible. BOT-05 does not provide an undo operation for destruction.

## 8. Concurrency & Race Safety

The storage boundary owns atomic claim/transition semantics. BOT-05 must not implement an in-memory boolean such as `frozen` or `deleted` as a substitute for durable state.

Restore, single-item destruction, and expiry purge must not both win for the same item. A store implementation must atomically claim the item for one lifecycle transition and reject incompatible concurrent claims.

## 9. Attack Surface

BOT-05 is hardened against:

- restore-after-expiry
- restore versus purge races
- delete-one versus restore races
- duplicate delete-one requests
- duplicate restore requests
- empty-trash partial failure
- stale or replayed item identifiers
- target collision during restore
- missing preservation payload
- retention-clock manipulation at the boundary
- cross-domain authority confusion
- destructive execution based only on UI intent
- accidental destruction of items outside the selected trash scope

## 10. Non-Responsibilities

BOT-05 does not own:

- identity or authentication
- ownership or permission policy
- approval decisions
- warning generation
- notifications
- Delete Bot authority decisions
- Archive lifecycle
- Mark/Mark All selection
- domain-specific restore conflict policy
- scheduler infrastructure
- UI rendering
- domain object serialization format

## 11. Architectural Principle

> **Trash preserves recoverability for the retention window; destruction is a separate irreversible lifecycle transition.**

And:

> **Presence in Trash is historical lifecycle state, not current authority.**
