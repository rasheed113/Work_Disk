# Work_Disk Web — Tools — BOT-06
# Archive 📦 — Architecture Blueprint

## 1. Purpose
BOT-06 is a domain-neutral lifecycle Tool Bot for moving an already-authorised resource into an archived state and returning it through an authorised unarchive lifecycle.

It is reusable by Inbox, Chat, Post, Notification, Document, Fleet/Entry, and future domain callers. The caller owns domain policy; BOT-06 owns only the archive lifecycle boundary.

## 2. Core invariants
- Archive is not Delete and not Trash.
- Archive does not create authority.
- A caller must supply authoritative permission/context.
- Archive preserves the resource identity and durable source reference.
- Archive must not silently destroy content.
- Repeated archive of the same logical request is idempotent.
- Repeated unarchive is idempotent or explicitly rejected; it must never duplicate the resource.
- An archived resource remains non-active according to the caller/domain projection; BOT-06 does not invent visibility semantics.
- Unarchive requires valid authority and a valid durable source/reference contract.
- Archive state is not proof of ownership or permission.
- Concurrent archive/unarchive operations resolve deterministically; no last-arrival winner.
- Crash/retry must not create duplicate archive records or lose the durable reference.
- Unsupported domain semantics require STOP rather than guessing.

## 3. Boundary
BOT-06 does not decide whether an item should be archived, who may archive it, where it appears in UI, retention policy, notification delivery, search, marking, sorting, deletion, trash, or domain-specific business rules.

The caller supplies the authoritative archive intent and context. BOT-06 validates the public contract and executes the lifecycle through injected persistence/execution interfaces.

## 4. Archive semantics
Archive means: retain the resource and its identity while transitioning its lifecycle representation to archived. It is not physical deletion, and it is not an automatic retention timer.

The resource must remain recoverable through the declared unarchive boundary unless the owning domain separately defines a lawful destruction transition.

## 5. Unarchive semantics
Unarchive returns the resource through the domain-provided restoration target/reference. BOT-06 does not assume a universal original location, ordering, unread state, notification state, or presentation position.

## 6. Multi-caller model
```text
Inbox Bot ───────┐
Chat Bot ────────┤
Post Bot ────────┤
Notification Bot ┤──→ BOT-06 Archive 📦
Document Bot ────┤
Future Bots ─────┘
```
All callers use the same boundary; domain-specific policy stays outside BOT-06.

## 7. Lifecycle
```text
Authorised Request
      ↓
Validate identity + authority + operation
      ↓
Archive claim / idempotency check
      ↓
Authoritative archive transition
      ↓
Archived
      ↓
Authorised Unarchive
      ↓
Unarchived through domain reference
```

## 8. Delete/Trash separation
Delete decides deletion through BOT-04. Trash owns deleted-item retention. BOT-06 must not convert an archive request into delete/trash, and Delete/Trash must not silently treat archive as deletion.

## 9. Public contract
Required concepts: request identity, operation, target type, target identity, authority reference, source/reference handle, and operation context. Concrete domain payloads stay behind opaque references.

## 10. Safety
If the target is missing, authority is absent, reference is invalid, lifecycle version conflicts, or an external transition cannot be confirmed, BOT-06 returns an explicit non-success outcome. It does not guess or claim completion.

## 11. Principle
> Archive preserves a resource as non-active state; it does not destroy it, manufacture authority, or define domain policy.
