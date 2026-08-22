# Dashboard View Mode Blueprint

## Runtime flow

`DashboardPreferences.viewMode`
→ `DashboardShell`
→ `.wd-dashboard-grid--grid` or `.wd-dashboard-grid--list`
→ responsive card layout

## UI
A compact `View` control exposes:
- Grid
- List

The selected option uses `aria-pressed` and is persisted with dashboard preferences.

## Default
Grid is the deterministic default.

## Responsive rule
Grid is two columns on wider screens and becomes one column below the mobile breakpoint. List remains one column.
