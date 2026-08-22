# Work_Disk Web — Dashboard View Mode v2.1 Contract

## Sealed rules

- `viewMode` is exactly `grid | list`.
- `gridColumns` is exactly `2 | 3 | 4`.
- Default state is `grid + 2`.
- Columns selector is presentation-only and is shown only for GRID.
- LIST is always one column.
- GRID remains a real grid on mobile; mobile responsive policy uses two columns to prevent oversized cards.
- Mode/column changes must not alter card order, hidden/unhidden state or pin state.
- Missing or invalid persisted `gridColumns` resolves to 2.
- No domain/service/repository dependency is permitted.
- No deletion is introduced by this feature.
