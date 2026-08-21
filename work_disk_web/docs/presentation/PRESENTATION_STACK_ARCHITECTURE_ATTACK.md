# Work_Disk Web Presentation Stack — Architecture Attack

## Status
ATTACK COMPLETE — candidate presentation stack selected for contract/blueprint phase.

## Repository evidence
`work_disk_web` currently contains documentation, source, and tests. The source tree currently exposes `account/` and `tools/` implementation areas, with no established browser presentation entry point or package manifest visible in the repository audit. The Dashboard roadmap therefore correctly blocks runtime UI implementation until a presentation stack is established.

## Attack target
The presentation stack must support the full Work_Disk Web ecosystem, not only Dashboard:

- reusable component-driven UI
- Dashboard and future screens
- context-aware capability presentation
- custom Dashboard preferences
- responsive web/mobile layouts
- accessibility
- routing and nested layouts
- typed integration with Work_Disk services
- testable components and user flows
- incremental adoption without moving domain ownership into UI code
- compatibility with the existing Work_Disk core/service architecture
- long-term maintainability without framework-specific domain coupling

## Candidates attacked

### React + TypeScript + Vite
**Result: PASS**

Strengths:
- React is explicitly component-oriented and supports composition of reusable UI pieces.
- TypeScript provides typed component contracts and integration boundaries.
- Vite provides the development server/build layer and supports React/TypeScript templates.
- React Router provides client-side routing and nested layout support.
- The stack can remain a browser presentation layer while Work_Disk domain ownership stays in existing services.

Risks controlled by architecture:
- React must not become the domain authority.
- UI state must not silently mutate authoritative records.
- Vite is a build/dev tool, not a domain/runtime replacement.
- Routing must remain separate from business ownership.

### Full-stack React framework
**Result: DEFERRED for initial Work_Disk Web presentation foundation**

Reason: the current repository does not establish a server-rendered React runtime, and introducing one would add a server/application boundary before the existing service integration boundary is defined. It can be reconsidered later if server rendering, route loaders, or server-side application behaviour becomes an explicit requirement.

### Vue / other component frameworks
**Result: REJECTED for this phase**

Reason: they can satisfy component requirements, but there is no repository evidence or architectural requirement that gives them an advantage over the React + TypeScript path. Introducing another framework would add an unnecessary ecosystem decision.

### Vanilla HTML/CSS/JavaScript
**Result: REJECTED for the full platform foundation**

Reason: it is viable for small pages but creates unnecessary manual composition/state/routing patterns for the planned large component ecosystem.

## Selected presentation foundation

**React + TypeScript + Vite + React Router + standards-based CSS/design tokens.**

This is a presentation-layer decision only. It does not change Work_Disk's core/domain architecture.

## Locked architectural boundaries

1. Presentation code owns rendering, interaction state, accessibility, navigation, and presentation preferences.
2. Domain services remain authoritative for identity, capabilities, records, permissions, notifications, media, and other business state.
3. Components consume explicit contracts/adapters; they do not reach directly into domain storage.
4. Dashboard customisation remains preference state: hide/unhide, add/remove from Dashboard, pin/unpin, ordering, and reset-to-default.
5. Removing a card from Dashboard never deletes the underlying feature or data.
6. Cards Gallery may display only registered and eligible components.
7. Context switching must not destructively erase another context's domain data or authoritative state.
8. Presentation components must be reusable outside Dashboard when their boundary is generic.
9. Responsive behaviour is a presentation concern; domain semantics must remain platform-neutral.
10. Test fixtures must never become production domain outcomes.

## Proposed stack layers

```text
Work_Disk Domain / Services
        ↓ explicit service contracts / adapters
Presentation Integration Layer
        ↓
React + TypeScript Component Layer
        ↓
Design Tokens / CSS / Accessibility Layer
        ↓
Browser

Build / Dev: Vite
Routing: React Router
Tests: TypeScript-aware component/contract test layer
```

## Dependency rule

`Domain → service contract → presentation adapter → component/page`

Never:

`Component → database/domain storage`

The UI must remain replaceable without rewriting authoritative domain logic.

## Attack conclusion

The repository needs a real presentation foundation before Dashboard runtime implementation. The best current fit is **React + TypeScript + Vite + React Router**, with a standards-based CSS/design-token layer and explicit service adapters.

The decision is now ready for the next gates:

**Boundary → Blueprint → Presentation Stack Contract → Roadmap → Implementation**

No runtime UI is claimed by this document.
