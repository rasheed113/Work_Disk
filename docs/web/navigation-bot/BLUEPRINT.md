# Work_Disk Web — Navigation Buttons Bot Blueprint

## Implementation sequence

1. Navigation registry: immutable destination definitions.
2. Surface visibility policy: explicit Dashboard/Feed decisions.
3. Presentation adapter: render navigation independently of Dashboard card composition.
4. Mobile adapter: viewport-fixed bottom presentation only for surfaces that enable it.
5. Tests: registry completeness, visibility policy, Dashboard-card isolation and responsive presentation contract.
6. Verification: repository tests, build and CI.

## Initial registry

- `/workspace/dashboard` → Dashboard
- `/workspace/finance` → Finance
- `/workspace/history` → History
- `/workspace/settings` → Settings
- `/workspace/profile` → Profile

## Surface policy

`dashboard` → visible
`social` / `feed` → hidden

Unknown surface identifiers default to hidden rather than inventing navigation behaviour.

## Architectural rule

The Dashboard shell consumes Navigation Buttons Bot output as a sibling presentation surface. It does not place navigation inside the dashboard card collection.
