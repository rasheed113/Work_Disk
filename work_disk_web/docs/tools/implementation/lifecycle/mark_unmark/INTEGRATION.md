# BOT-09 — Mark / Unmark 🔖 Integration Contract

## Caller contract
A page/domain caller supplies request identity, authority reference, scope reference, and target references. UI code may invoke BOT-09 after entering selection mode.

## Selection contract
BOT-09 returns a selection snapshot for the supplied scope. Callers must not use a snapshot as proof of permission to perform another action.

## Action discovery contract
A separate action/capability layer may inspect the current context and selection to expose applicable actions. It must not make BOT-09 responsible for Delete, Move, Archive, Download, Export, Upload, or future action policy.

## Downstream action contract
When an action is chosen, the corresponding Tool Bot receives the selected scope/targets and performs its own fresh authority, lifecycle, and conflict checks.

## Mark All contract
The store/domain defines which targets are selectable in the supplied scope. BOT-09 never expands a scope beyond what the caller provides.

## Cross-page rule
The same BOT-09 boundary can serve multiple pages/domains, but a selection cannot cross scope boundaries unless the caller explicitly supplies a common authorised scope.
