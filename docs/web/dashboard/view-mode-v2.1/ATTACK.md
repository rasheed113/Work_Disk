# Work_Disk Web — Dashboard View Mode v2.1 Attack

## Attacks

1. **Mode/state confusion** — GRID/LIST must not alter card order, pinning or hidden state.
2. **Column corruption** — only 2, 3 and 4 are valid persisted values; invalid storage falls back to default 2.
3. **Mobile collapse** — GRID must remain GRID on mobile; responsive CSS may reduce column density but must not switch semantic mode.
4. **Domain leakage** — no view-mode code may call domain services or repositories.
5. **Destructive customisation** — changing view or columns must never delete cards or domain data.
6. **Persistence drift** — existing v1 preferences remain readable; missing `gridColumns` receives default 2.

## Result
All attacks are addressed at the presentation boundary and covered by the dashboard contract tests.
