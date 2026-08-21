# Dashboard Implementation Contract

## Scope
Implement the 12 locked dashboard component boundaries without moving domain ownership into the dashboard layer.

## Contract invariants
1. Dashboard composition must be deterministic for the supplied account/context/capability state.
2. A hidden component remains available to the underlying system and may be restored without data reconstruction.
3. Removing a component from the dashboard never deletes its feature, capability, or domain data.
4. Dashboard preferences must not mutate authoritative domain records.
5. Context switching must not clear another context's dashboard data or preferences unless an explicit, authorised preference operation requires it.
6. Cards Gallery may expose only registered and eligible components.
7. Reset-to-default changes presentation preferences only.
8. Component ordering must be stable and deterministic for equal preference versions.
9. Invalid/stale component identifiers in preferences must be safely ignored or reconciled without destructive domain mutation.
10. No production behaviour may depend on hardcoded test fixtures or fabricated domain outcomes.

## Preference model
Dashboard preference state should support:
- visible/hidden
- pinned/unpinned
- ordered position
- selected components
- preference version
- context scope

## Non-goals
- Domain record deletion
- Account lifecycle mutation
- Capability creation/revocation
- Authentication
- Notification delivery
- Media acquisition

Those concerns remain with their authoritative services/tools.

## Acceptance gate
The dashboard implementation is complete only after contract tests, documentation, PR review, merge, main verification, and Master Menu update.
