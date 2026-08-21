# BOT-09 — Mark / Unmark 🔖 Implementation Contract

## Command contract
Mark, Unmark, Mark All, and Clear requests carry request identity, opaque authority reference, and opaque scope reference. Individual operations also carry an opaque target type/id.

## Authority contract
The caller/domain supplies MarkAuthority. BOT-09 invokes it before any selection-store operation. BOT-09 never manufactures permission.

## Selection-store contract
The caller/domain supplies MarkSelectionStore. The store owns selection persistence/consistency and scope membership. BOT-09 does not query domain databases directly.

## Result contract
Results are explicit: Marked, Unmarked, AlreadyMarked, AlreadyUnmarked, MarkAllApplied, Cleared, InvalidRequest, InvalidScope, AuthorityRejected, and SelectionConflict.

## Isolation invariant
A selection is always associated with one opaque scope reference. BOT-09 must not infer ownership from page names, target types, field names, or UI routes.

## Mark All invariant
Mark All means all selectable targets within the supplied authorised scope, as defined by the domain/store. It never means every record in the application.

## Action independence invariant
A marked target is not an action authorisation. Downstream tools must perform fresh authority and state validation before executing Delete, Move, Archive, Download, Export, Upload, or any other operation.

## UI independence
BOT-09 contains no long-press, checkbox, toolbar, bottom-sheet, navigation, or presentation logic.

## Payload invariant
Selection snapshots contain opaque target references only. No domain record payload, sensitive field, or action policy is exposed by BOT-09.

## Hardcoding prohibition
No domain/page/action/permission/lifecycle/notification policy is hardcoded into BOT-09.
