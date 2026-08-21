# BOT-09 — Mark / Unmark 🔖 Blueprint

## Purpose
BOT-09 is a reusable, multi-caller selection Tool Bot. It manages individual mark/unmark, Mark All within an authorised scope, and clearing selection.

## Boundary
Caller/domain/authority owns:
- account, role, relationship, and permission policy
- construction of the searchable/selectable scope
- target lifecycle visibility
- UI presentation and selection-mode gestures
- available-action discovery
- downstream action execution and confirmation

BOT-09 owns:
- structural request validation
- invoking the supplied authority boundary before store access
- delegating selection state to the supplied selection store
- returning an explicit selection snapshot/result
- keeping selection scoped to an opaque scope reference

## Selection model
Two representations are supported:
- Individual: explicit marked target references
- AllInScope: logical Mark All within the supplied authorised scope

## Action model
BOT-09 does not enumerate or execute actions. Delete, Move, Archive, Download, Export, Upload, and future tools are discovered by a separate action/capability layer and each downstream tool rechecks its own authority.

## UI model
Long press, checkboxes, Mark All controls, selection toolbar, bottom action sheet, and action icons are presentation concerns. They may call BOT-09 but are not embedded in it.

## Non-goals
BOT-09 does not delete, move, archive, restore, export, upload, download, notify, grant permission, decide ownership, or define lifecycle policy.

## Failure semantics
Invalid requests, authority rejection, invalid scope, and selection conflict remain distinguishable. Empty selection is a valid state, not an error.
