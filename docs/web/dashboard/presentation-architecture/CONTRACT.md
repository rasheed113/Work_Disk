# Work_Disk Web — Dashboard Presentation Contract

## Sealed rules

1. The Dashboard registry contains exactly **twelve locked boundaries**.
2. Exactly **eight registry boundaries are user-facing Dashboard content surfaces**: Profile, Smart Clock, Ticker / Status, Quick Actions, Summary / KPI, Activity, Notifications and Capabilities.
3. The remaining four registry boundaries — Header, Navigation, Custom Dashboard and Cards Gallery — are infrastructure/presentation boundaries and are **not rendered as ordinary Dashboard cards**.
4. Workspace Navigation is the single authoritative primary navigation surface.
5. Dashboard-local Dashboard/Features/Settings navigation must not render.
6. Customize is ephemeral presentation state and is never rendered as a permanent Dashboard card.
7. Cards Gallery/registry infrastructure is not ordinary Dashboard content.
8. Normal mode does not expose Hide, Unhide, Pin, Unpin or Move controls inside runtime card headers.
9. Customize Mode may expose existing non-destructive Hide/Unhide, Pin/Unpin and Reorder operations through one management surface.
10. Grid/List remains exactly `grid | list`.
11. Grid Columns remains exactly `2 | 3 | 4` and defaults to `2`.
12. Mobile responsive policy may constrain rendered density without changing the stored Grid Columns preference.
13. Dashboard presentation must not access domain services, repositories or persistence directly.
14. Existing Tool-Bots may be exposed only after an explicit authorised Dashboard caller/integration contract exists. Search/Filter/Sort are not invented here.
15. Empty states remain truthful to the supplied Dashboard model.
16. Legacy/unknown persisted identifiers are normalised against the twelve-boundary registry without destructive changes to valid content preferences.
17. Reordering operates only on the eight content surfaces; registry-only boundaries remain outside mutable card order semantics.
