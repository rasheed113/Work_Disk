# Dashboard View Mode Architecture

## Status
SEALED for implementation.

## Decision
The Dashboard supports two presentation view modes:
- `grid` — default, two columns on wider screens and one column on small mobile screens.
- `list` — one full-width column.

View mode is presentation preference state. It does not represent account, role, capability, domain, or service state.

## Invariants
1. Changing Grid/List never changes card identity.
2. Changing Grid/List never changes card order.
3. Changing Grid/List never changes hidden/unhidden state.
4. Changing Grid/List never changes pinned state.
5. Changing Grid/List never mutates authoritative domain records.
6. View mode persists as a dashboard presentation preference only.
7. Invalid stored view modes reconcile to the default Grid mode.
8. Responsive CSS may adapt Grid to one column on small screens without changing the selected semantic mode.

## Ownership
Dashboard preference state owns the selected view mode. Dashboard Shell consumes it to choose presentation layout. Domain services remain outside this boundary.
