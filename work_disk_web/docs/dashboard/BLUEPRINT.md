# Dashboard Component Blueprint

## Proposed implementation tree

```text
dashboard/
├── shell/
├── header/
├── profile/
├── navigation/
├── smart_clock/
├── ticker/
├── quick_actions/
├── summary/
├── activity/
├── notifications/
├── capability_cards/
└── customisation/
    ├── cards_gallery/
    ├── visibility/
    ├── ordering/
    ├── pinning/
    └── reset/
```

## Dependency direction

`Dashboard Shell` composes components. Components may consume authorised read/presentation contracts but must not bypass domain ownership boundaries.

`Customisation` manages dashboard preference state. `Cards Gallery` discovers eligible dashboard components through the component registry/contract; it does not create domain capabilities.

## Component registry requirements

Each dashboard component must expose stable metadata sufficient for selection and rendering:
- component identifier
- display name
- category
- availability predicate/context requirement
- default visibility
- default order
- pin capability
- version

No registry entry may imply that a feature exists unless the underlying capability is verified.
