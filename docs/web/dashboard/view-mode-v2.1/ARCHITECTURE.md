# Work_Disk Web — Dashboard View Mode v2.1 Architecture

## Scope
Presentation-only dashboard layout preference.

## Modes
- GRID — default.
- LIST — one-column presentation.

## Grid columns
- 2 — default.
- 3.
- 4.

## Mobile rule
Mobile does not silently convert GRID into LIST. GRID remains a two-dimensional grid. On narrow screens, 3- and 4-column selections safely collapse to two columns to preserve readable card dimensions; LIST remains one column.

## Authority
View mode and grid columns are presentation preferences. They do not own or mutate domain data, account authority, card semantics, hidden state, pin state, or ordering semantics.
