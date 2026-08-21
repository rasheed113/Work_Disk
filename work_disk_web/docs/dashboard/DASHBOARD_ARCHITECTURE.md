# Work_Disk Dashboard Architecture

## Status
DESIGNED — architecture attack and boundary locked; implementation contract follows.

## Purpose
The dashboard is a context-aware presentation layer. It is not an Account Type, domain owner, or destructive data boundary.

## Architecture Attack
The initial 12-component proposal was attacked against ownership, reuse, lifecycle, context switching, customisation, and dependency boundaries.

Result: 12 core component boundaries survive. Custom Dashboard and Cards Gallery remain one core board with two internal logical sub-boundaries.

## Core Components
1. Dashboard Shell
2. Header
3. Profile
4. Navigation
5. Smart Clock
6. Ticker / Status Strip
7. Quick Actions
8. Summary / KPI Cards
9. Activity / Recent Items
10. Notifications Panel
11. Feature / Capability Cards
12. Custom Dashboard + Cards Gallery

## Locked Rules
- Dashboard presents state; it does not own domain data.
- Account identity remains outside dashboard ownership.
- Context changes must not destructively erase or overwrite another context's data.
- Hide and Remove-from-Dashboard are presentation/layout operations.
- Delete is not a dashboard customisation operation.
- Unhide restores visibility without recreating domain data.
- A capability card is shown only when its underlying capability is available to the current context.
- Customisation is persisted as user/dashboard preference state, not domain mutation.
- Components must remain reusable where their boundary is not dashboard-specific.

## Boundary Decision
Dashboard Shell owns composition and layout only.
Header, Profile, Navigation, Smart Clock, Ticker, Quick Actions, Summary, Activity, Notifications and Capability Cards own presentation concerns within their respective boundaries.
Custom Dashboard owns layout preferences: add/remove from dashboard, hide/unhide, pin/unpin, ordering and reset-to-default. Cards Gallery owns discovery/selection of eligible dashboard components within that same board.
