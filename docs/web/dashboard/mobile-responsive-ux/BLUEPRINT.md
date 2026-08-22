# Work_Disk Web — Dashboard Mobile Responsive UX Blueprint

## Runtime flow

1. Dashboard Shell reads presentation preferences.
2. View Mode selects Grid or List.
3. Grid Columns selects 2, 3 or 4 as the stored presentation preference.
4. Responsive CSS applies the sealed mobile density policy: mobile Grid renders two physical columns.
5. Card surfaces contain their intrinsic content with `min-width: 0`, wrapping and bounded nested grids.
6. Customize Mode exposes management controls only while editing.
7. Existing hide, pin and reorder operations are invoked unchanged.

## Normal mode

The Dashboard prioritises content and primary navigation. Card-management controls are not permanently exposed.

## Customize mode

The Dashboard exposes presentation-management controls and view configuration while keeping the same underlying card order, hidden state, pinned state and domain data.

## Responsive target

- Desktop: 2/3/4 physical columns according to the selected preference and breakpoint policy.
- Mobile Grid: 2 physical columns to preserve the real Grid experience without overflow.
- Mobile List: 1 physical column.
- Child content must not widen the viewport.
