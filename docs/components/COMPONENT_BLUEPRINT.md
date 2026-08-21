# Work_Disk Web Component System Blueprint

## Package shape

```text
work_disk_web/
└── src/presentation/
    ├── app/
    ├── routing/
    ├── theme/
    │   ├── tokens/
    │   ├── typography/
    │   ├── motion/
    │   └── surfaces/
    ├── primitives/
    │   ├── layout/
    │   ├── responsive/
    │   └── accessibility/
    ├── components/
    │   ├── actions/
    │   ├── feedback/
    │   ├── identity/
    │   ├── containers/
    │   ├── inputs/
    │   ├── data-display/
    │   └── overlays/
    ├── specialised/
    │   ├── profile/
    │   ├── capability/
    │   ├── notification/
    │   ├── activity/
    │   ├── media/
    │   ├── chat/
    │   └── feed/
    ├── dashboard/
    ├── adapters/
    ├── contracts/
    └── registry/
```

## Component contract shape

Every reusable component defines, as applicable:

- typed props/input contract
- rendered state contract
- event/output contract
- accessibility contract
- responsive behaviour
- motion behaviour
- visual token dependencies
- error/empty/loading behaviour
- test boundary

## Visual system

Work_Disk UI is bright and professional, uses reusable 3D depth/surface primitives, supports controlled animation, keeps cards at professional medium sizing, and remains responsive across mobile, tablet and desktop.

## Dependency direction

```text
Domain / Services
       ↓
Typed Contracts / Adapters
       ↓
Presentation Components
       ↓
Design Primitives / Tokens
```

Presentation components must not reverse this direction.

## Reuse rule

Specialised feature components may compose generic components. Generic components must not import specialised feature/domain modules.

## Dashboard relationship

Dashboard components compose this system. The reusable component system does not redefine the Dashboard's 12 locked core boundaries.
