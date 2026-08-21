# BOT-05 — Trash 🗑️ Tool Bot Profile

## Identity
- **Number:** BOT-05
- **Name:** Trash 🗑️ Bot
- **Category:** Tools / Lifecycle
- **Location:** `src/tools/lifecycle/trash`

## Primary capability
Own the bounded lifecycle of resources already admitted to Trash.

## Accepts calls from
Any authorised Work_Disk domain/tool that has a valid Trash lifecycle contract. BOT-05 is not restricted to one domain such as Fleet.

## Can
- accept a durable Trash entry
- retain restore metadata/reference
- restore an eligible item through the restore boundary
- permanently destroy one claimed item
- empty the current Trash scope
- purge expired items
- return explicit lifecycle results

## Cannot
- decide ownership
- decide permissions
- decide approvals
- send notifications
- serialize domain objects
- invent restore conflict policy
- bypass preservation rules
- act on arbitrary non-Trash identifiers
- use UI intent as authority

## Retention
Three calendar months, supplied through the authoritative retention policy boundary.

## Safety principle
**Recoverability is time-bounded; permanent destruction is explicit and irreversible.**
