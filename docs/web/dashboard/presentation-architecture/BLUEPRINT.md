# Work_Disk Web — Dashboard Presentation Blueprint

## Normal Mode

```text
Workspace Shell
└── Dashboard
    ├── Header / Account Context
    ├── Presentation Controls
    │   ├── Grid / List
    │   ├── Columns (Grid only)
    │   └── Customize
    └── Content Grid/List
        ├── Profile
        ├── Smart Clock
        ├── Ticker / Status
        ├── Quick Actions
        ├── Summary / KPI
        ├── Activity
        ├── Notifications
        └── Capabilities
```

## Customize Mode

```text
Dashboard
├── Presentation Controls (Done)
├── Customize Dashboard panel
│   ├── Hide / Unhide
│   ├── Pin / Unpin
│   ├── Move Up / Down
│   └── Reset to Default
└── Dashboard content
```

## Not rendered as Dashboard content
- Workspace Navigation
- Card registry / Cards Gallery infrastructure
- Internal card definitions

## Responsive rule
Stored Grid Columns remains 2/3/4. Narrow mobile rendering remains a real two-column Grid; the responsive policy constrains rendered density without mutating the stored preference.
