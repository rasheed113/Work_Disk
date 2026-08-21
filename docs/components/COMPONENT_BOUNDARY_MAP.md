# Work_Disk Web Component Boundary Map

## Status

SEALED for the reusable presentation-component foundation.

## Boundary rules

- Components are presentation boundaries, not domain authorities.
- Components consume typed presentation contracts or adapters.
- Components do not access SQLite, repositories, or domain persistence directly.
- A component becomes an independent boundary when it has a reusable visual contract, meaningful lifecycle/state, accessibility contract, or cross-feature reuse.
- Pure styling primitives remain infrastructure.
- Dashboard-specific composition remains separate from the generic component system.

## Layer 1 — Foundation

1. Design Tokens
2. Typography
3. Layout Primitives
4. Responsive Primitives
5. Motion / Animation Primitives
6. Elevation / 3D Surface Primitives

## Layer 2 — Core UI

7. Button
8. Icon Action
9. Badge
10. Avatar
11. Tooltip
12. Divider
13. Loading State
14. Empty State
15. Error State

## Layer 3 — Containers

16. Card
17. Panel
18. Section
19. Grid
20. Stack
21. Dialog / Modal
22. Drawer

## Layer 4 — Input and Data

23. Text Input
24. Select
25. Checkbox
26. Toggle
27. Search
28. Filter
29. Form
30. List
31. Table

## Layer 5 — Work_Disk Specialised Components

32. Profile Component
33. Capability Component
34. Notification Component
35. Activity Component
36. Media Component
37. Chat Component
38. Feed Component
39. Dashboard Card Infrastructure
40. Cards Gallery Infrastructure

## Non-boundary infrastructure

- Shared icon set
- Utility functions
- Test fixtures
- Theme provider
- Component registry metadata

These support components but do not become independent Work_Disk domain boundaries.

## Dashboard relationship

The existing 12 Dashboard boundaries remain authoritative for Dashboard composition. Generic components such as Card and Dashboard Card Infrastructure must not silently create additional Dashboard core boundaries.
