# Work_Disk Web — Dashboard Presentation Contract

## Sealed rules

1. Workspace Navigation is the single authoritative primary navigation surface.
2. Dashboard-local Dashboard/Features/Settings navigation must not render.
3. Dashboard content contains only user-facing Dashboard cards from the approved content registry.
4. Customize is ephemeral presentation state and is never rendered as a permanent Dashboard card.
5. Cards Gallery/registry infrastructure is not ordinary Dashboard content.
6. Normal mode does not expose Hide, Unhide, Pin, Unpin or Move controls inside runtime card headers.
7. Customize Mode may expose existing non-destructive Hide/Unhide, Pin/Unpin and Reorder operations through one management surface.
8. Grid/List remains exactly `grid | list`.
9. Grid Columns remains exactly `2 | 3 | 4` and defaults to `2`.
10. Mobile responsive policy may constrain rendered density without changing the stored Grid Columns preference.
11. Dashboard presentation must not access domain services, repositories or persistence directly.
12. Existing Tool-Bots may be exposed only after an explicit authorised Dashboard caller/integration contract exists. Search/Filter/Sort are not invented here.
13. Empty states remain truthful and must not fabricate domain records.
14. Legacy persisted presentation-only card identifiers are migrated out without destructive changes to valid Dashboard content preferences.
