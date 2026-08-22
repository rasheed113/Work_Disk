# Dashboard View Mode Boundary

## Presentation-owned
- `DashboardViewMode` type
- preference persistence
- Grid/List selector UI
- dashboard layout class selection
- responsive layout rules

## Explicitly outside boundary
- Account identity
- Profile authority
- Capability lifecycle
- Domain records
- Repositories and database access
- Authentication and session authority

## Boundary rule
The View Mode feature may read and write only dashboard presentation preferences. It must never become a gateway to authoritative domain state.
