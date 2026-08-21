# BOT-09 — Mark / Unmark 🔖 Attack Register

## Attack review

- 09A Scope omission — reject requests without an opaque selection scope.
- 09B Authority omission — reject requests without an authority reference.
- 09C Cross-account selection — authority/scope must constrain marking before store access.
- 09D Cross-role selection — role/context changes cannot silently broaden scope.
- 09E Mark-as-permission — a marked target is never an authority grant.
- 09F Mark-as-action — marking performs no Delete, Move, Archive, Export, Upload, or other action.
- 09G Cross-page contamination — selections are isolated by opaque scope reference.
- 09H Mark-All escape — Mark All applies only within the authorised supplied scope.
- 09I Unbounded Mark-All — the store/domain owns the scope membership; BOT-09 never invents a global universe.
- 09J Stale selection — action tools must revalidate authority/state when executed.
- 09K Deleted target — lifecycle visibility/removal is domain/store policy; BOT-09 does not resurrect or mutate targets.
- 09L Concurrent selection — store owns selection consistency and conflict semantics.
- 09M Replay — repeated mark/unmark must remain idempotent at the store boundary.
- 09N Invalid target — target type/id are structurally required.
- 09O Empty selection — clear/empty state is valid and distinguishable from failure.
- 09P UI coupling — long-press, checkboxes, toolbars, and action sheets remain presentation concerns.
- 09Q Action discovery coupling — BOT-09 does not hardcode or enumerate Delete/Move/Archive/etc.
- 09R Action authority — every downstream action performs its own fresh authority validation.
- 09S Selection leakage — snapshots expose only the supplied scope's selection.
- 09T Sensitive data — selection contains opaque target references, not domain payloads.
- 09U Mark-All representation — AllInScope avoids requiring BOT-09 to materialise an unbounded list.
- 09V Context loss — scope reference remains mandatory for every operation.
- 09W Clear isolation — clearing one scope cannot clear another scope.
- 09X Provider/store failure — conflict is explicit and does not fabricate a successful selection.
- 09Y Capability confusion — available actions are resolved outside BOT-09 from current context/capabilities.
- 09Z Boundary drift — new selection behaviour must preserve scope, authority, read/write separation, and action independence.

## Verdict
All identified architecture-level attacks are converted into explicit BOT-09 boundaries or downstream store/action responsibilities. No unresolved architecture blocker remains for the generic Mark / Unmark Tool Bot.
