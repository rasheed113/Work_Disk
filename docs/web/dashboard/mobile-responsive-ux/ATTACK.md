# Work_Disk Web — Dashboard Mobile Responsive UX Attack

## Attack findings

### P0 — Horizontal overflow
3/4-column selections could impose content pressure on narrow mobile tracks. The existing View Mode contract already defines a two-column mobile rendering policy; the implementation must enforce that policy without allowing child content to widen the viewport.

### P1 — Card content pressure
Card headers and nested grids can create minimum-content pressure. `min-width: 0`, bounded children, wrapping and overflow containment are required at presentation boundaries.

### P1 — Toolbar density
View and column controls plus permanent card controls create unnecessary mobile cognitive load.

### P2 — Permanent card controls
Pin, move and Hide are useful in customization but should not dominate normal viewing.

### P2 — Empty-state repetition
Repeated empty-state messages are legitimate evidence but should remain concise and visually subordinate.

## Rejected shortcuts

- Do not force the entire Dashboard into List mode on mobile.
- Do not delete or silently remove empty cards.
- Do not change domain/service contracts to solve presentation problems.
- Do not invent production data.

## Result

The attack identifies a presentation-only solution: harden responsive constraints and expose management controls through an ephemeral Customize Mode.
