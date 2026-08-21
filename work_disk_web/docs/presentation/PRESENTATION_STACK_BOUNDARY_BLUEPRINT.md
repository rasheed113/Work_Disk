# Work_Disk Web Presentation Stack — Boundary & Blueprint

## Status
BOUNDARY AND BLUEPRINT COMPLETE — implementation-ready presentation boundary.

## 1. Boundary

The presentation stack is a replaceable UI layer. It renders state supplied through explicit service contracts/adapters and owns presentation behaviour only.

### Presentation owns
- rendering and component composition
- local interaction state
- accessibility behaviour
- navigation and route composition
- responsive layout
- presentation preferences
- dashboard customisation preferences
- loading, empty, and error presentation

### Presentation does not own
- identity authority
- account lifecycle
- domain records
- permissions authority
- authoritative notifications
- media ownership
- reconciliation authority
- database/storage decisions
- domain deletion or destructive mutation rules

## 2. Integration boundary

```text
Work_Disk Core / Domain Services
          |
          v
Explicit service contracts / adapters
          |
          v
Presentation integration layer
          |
          v
Pages + reusable components
          |
          v
Design tokens + CSS + accessibility
          |
          v
Browser
```

No presentation component may directly access domain storage.

## 3. Proposed project blueprint

```text
work_disk_web/
  src/
    presentation/
      app/
      routes/
      layouts/
      pages/
      components/
        common/
        dashboard/
        navigation/
        feedback/
      state/
      adapters/
      contracts/
      accessibility/
      styles/
      registry/
  tests/
    presentation/
      components/
      contracts/
      flows/
  docs/
    presentation/
```

The exact implementation paths may be adjusted if the implementation audit finds an existing compatible structure; no duplicate parallel UI architecture should be created.

## 4. Component rules

Reusable components must have explicit inputs and outputs and remain domain-agnostic where possible. Domain-specific behaviour enters through adapters/contracts rather than direct storage access.

Dashboard components consume the same presentation component model as future Work_Disk screens.

## 5. Routing boundary

React Router owns URL-to-page composition and nested layout selection. Route definitions must not become domain authorization authority. Authoritative permission/capability decisions remain in service contracts.

## 6. State boundary

Presentation state is divided into:
- ephemeral interaction state
- server/service-derived view state
- presentation preferences

Authoritative domain state remains outside the presentation layer.

## 7. Styling boundary

Use standards-based CSS and design tokens. Tokens define shared spacing, typography, sizing, elevation, motion, responsive breakpoints, and semantic UI states. Components must not hard-code domain-specific visual semantics into business logic.

## 8. Responsive boundary

Responsive behaviour is implemented at the presentation layer. Mobile, tablet, and desktop layouts may differ visually while preserving the same domain meaning and service contracts.

## 9. Testing boundary

Presentation tests verify rendering, interaction, accessibility-critical behaviour, navigation, contract mapping, and non-destructive customisation. Test fixtures must not be treated as production domain outcomes.

## 10. Dashboard integration

The dashboard consumes the presentation stack through its locked 12-component baseline. Custom Dashboard preferences remain presentation preference state:

- hide / unhide
- add / remove from dashboard
- pin / unpin
- reorder
- reset to default
- Cards Gallery selection

Removing or hiding a card never deletes the underlying feature or data.

## 11. Boundary attack result

PASS. No additional top-level presentation boundary is required at this stage. The architecture remains extensible for future components without granting UI code domain authority.

## 12. Exit criteria

Implementation may begin only when:
- this boundary and blueprint are accepted through the normal PR gate;
- the presentation contract is sealed;
- the implementation roadmap identifies incremental vertical slices;
- tests are defined for each implemented slice.
