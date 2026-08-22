# Work_Disk Web — Dashboard Presentation Architecture

## Purpose
Define the user-facing Dashboard composition after the #84 visual review while preserving the sealed View Mode and presentation-only boundaries.

## Target hierarchy

`Workspace Shell → Dashboard Header/Context → Presentation Controls → Dashboard Content → Optional Customize Mode`

### Global shell
Owned by the Workspace Shell. Primary navigation is owned and rendered by the dedicated Navigation Buttons Bot as a sibling presentation boundary, never as Dashboard content.

### Dashboard header/context
`Header` presents Work_Disk and the current account context. It does not own identity authority.

### Presentation controls
Normal mode exposes only presentation actions already authorised by the Dashboard contract:
- Grid / List
- Grid Columns when Grid is active
- Customize

Search, Filter and Sort are not added until an explicit Dashboard caller/integration contract authorises the existing Tool-Bots.

### Dashboard content
The user-facing content surfaces are:
1. Profile
2. Smart Clock
3. Ticker / Status
4. Quick Actions
5. Summary / KPI
6. Activity
7. Notifications
8. Capabilities

### Customize Mode
Customize is ephemeral UI state. When active, a dedicated management surface exposes Hide/Unhide, Pin/Unpin, Move Up/Down and Reset to Default. These operations remain non-destructive and presentation-only.

### Non-content surfaces
Workspace Navigation and Cards Gallery/registry infrastructure are not Dashboard cards. The Navigation Buttons Bot owns navigation presentation and surface visibility. The Dashboard does not register navigation as ordinary content.

## Preserved invariants
- Grid/List remains exactly `grid | list`.
- Stored Grid Columns remains exactly `2 | 3 | 4`.
- Mobile rendering may constrain density without rewriting the stored preference.
- Dashboard does not access domain repositories/services directly.
- Empty states remain truthful to the supplied Dashboard model.
- No Account, Profile, capability, permission or Tool-Bot authority is moved into Dashboard presentation.
