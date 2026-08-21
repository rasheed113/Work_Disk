# Dashboard Runtime Vertical Slice

## Scope

This slice implements the first Work_Disk Web Dashboard runtime using the sealed Dashboard architecture and presentation-stack contract.

## Core boundaries

1. Dashboard Shell
2. Header
3. Profile
4. Navigation
5. Smart Clock
6. Ticker / Status
7. Quick Actions
8. Summary / KPI Cards
9. Activity / Recent Items
10. Notifications Panel
11. Feature / Capability Cards
12. Custom Dashboard + Cards Gallery

The registry represents the locked twelve core boundaries. The shared `DashboardCard` is presentation infrastructure and is not counted as a thirteenth core boundary.

## Personalisation rules

- Hide and Unhide are supported.
- Add/Remove from Dashboard is represented through visibility controls; removing a card from the dashboard does not delete the feature or its data.
- Pin and Unpin are supported.
- Reorder is supported through move controls.
- Reset to Default is supported.
- Preferences persist locally under a versioned storage key.
- Dashboard personalisation does not become domain authority.

## Data boundary

The runtime accepts a typed `DashboardModel`. No database access is performed by presentation components. No fabricated production records are introduced. Empty states are rendered when authoritative data is unavailable.

## Verification

The slice includes registry/invariant tests and the existing TypeScript/Vite build and typecheck commands. CI status must be reported from GitHub rather than assumed.
