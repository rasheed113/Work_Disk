# Dashboard View Mode Contract

## Contract
`DashboardViewMode = grid | list`.

Grid is the default.

## Required behaviour
1. Selecting Grid renders the dashboard in grid presentation.
2. Selecting List renders the dashboard in list presentation.
3. Selection is persisted in dashboard preference storage.
4. Rehydration accepts only `grid` or `list`.
5. Invalid persisted values fall back to Grid.
6. View mode changes never mutate `hidden`, `pinned`, or `order` preference state.
7. View mode changes never mutate domain data.
8. The selector is accessible through semantic buttons and `aria-pressed`.
9. Reduced-motion users receive no required motion for view switching.
10. Existing 12-card boundaries, Custom Dashboard, and Cards Gallery remain intact.

## Acceptance
The feature is complete only after tests, docs, PR review, merge, main verification, and Master Menu update.
