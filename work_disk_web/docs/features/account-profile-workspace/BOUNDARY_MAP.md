# Account/Profile + Workspace — Boundary Map

## Feature boundaries

1. **Account Context Surface** — displays authoritative account identity context supplied by an adapter.
2. **Profile Surface** — displays profile information supplied by the profile contract; no profile mutation is owned here.
3. **Workspace Shell** — owns presentation layout, navigation framing and active route state.
4. **Workspace Navigation** — routes to feature surfaces; it does not grant permissions or capabilities.
5. **Profile Empty State** — represents unavailable authoritative profile context without inventing data.

## Dependency direction

`Domain -> adapter/model -> feature surface -> reusable components`

No feature surface imports repository/database implementations.

## Route boundaries

- `/workspace` — Workspace Shell
- `/profile` — Account/Profile Surface
- `/dashboard` — existing Dashboard Surface

Unknown routes continue to resolve through the application routing policy.
