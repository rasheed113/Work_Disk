# Work_Disk Web — Dashboard View Mode v2.1 Blueprint

1. Extend the Dashboard presentation model with `DashboardGridColumns = 2 | 3 | 4`.
2. Extend dashboard preferences with `gridColumns`, defaulting to 2.
3. Validate stored values; missing/invalid values use 2.
4. Expose a Columns selector only while GRID is selected.
5. Apply the selected column count through presentation CSS classes.
6. Keep LIST one column.
7. At mobile widths, retain GRID semantics and use two compact columns for all grid selections.
8. Preserve card order, hidden/unhidden state and pin state throughout mode/column changes.
