# Work_Disk Web — Dashboard Presentation Boundary Map

## Boundaries

1. **Workspace Shell** — owns global workspace framing and primary navigation.
2. **Dashboard Header** — presents Work_Disk/account context supplied to the Dashboard.
3. **Dashboard Presentation Controls** — owns Grid/List, Grid Columns and entry/exit of Customize Mode.
4. **Dashboard Content** — presents authoritative domain-neutral Dashboard model data.
5. **Customize Mode** — owns presentation-only visibility, pinning and ordering operations.
6. **Tool-Bot integration boundary** — Dashboard may call an existing Tool-Bot only after a caller contract explicitly authorises the Dashboard as a caller.

## Explicit exclusions

- Dashboard does not own Account identity.
- Dashboard does not own Profile authority.
- Dashboard does not grant permissions or capabilities.
- Dashboard does not access SQLite or repositories directly.
- Dashboard does not expose internal card registries as ordinary content.
- Dashboard does not invent Search/Filter/Sort contracts.

## Navigation rule
There is one authoritative Workspace Navigation surface. Dashboard-local duplicate navigation is prohibited.
