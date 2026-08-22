# Work_Disk — Master Menu

> Living inventory of what Work_Disk actually contains. This document is updated only after a change is implemented, reviewed, merged, and verified on `main`.

## Status Rules
- **IMPLEMENTED** — present on `main` and verified.
- **DESIGNED** — architecture/contract exists, implementation is not yet verified on `main`.
- **IN PROGRESS** — active implementation work.
- **DEFERRED** — intentionally postponed by architecture decision.
- **CANDIDATE** — under audit; not part of the implemented inventory.

## 1. Repository Map — Verified
- `docs/` — architecture and implementation documentation
- `src/` — implementation source
- `tests/` — test source
- `src/account/` — account implementation area
- `src/tools/` — Tool-Bot implementations
- `docs/account/` — account documentation
- `docs/profiles/` — profile documentation
- `docs/tools/` — Tool-Bot documentation

## 2. Core System
- Work_Disk architecture and contracts — **IMPLEMENTED/DOCUMENTED**
- Account foundation — **IMPLEMENTED**
- Profile authority and assembly — **IMPLEMENTED**
- Tool-Bot architecture/boundary model — **IMPLEMENTED**
- Contract/implementation/test/documentation workflow — **IMPLEMENTED**

## 3. Tool-Bot Inventory
### BOT-01 → BOT-60
- BOT-01 → BOT-60 — **IMPLEMENTED**

## 4. Cross-System Capabilities
- Identity / Account — **IMPLEMENTED**
- Profiles — **IMPLEMENTED**
- Record lifecycle — **IMPLEMENTED**
- Search / Filter / Sort — **IMPLEMENTED**
- Selection / Actions — **IMPLEMENTED**
- Social / Feed — **IMPLEMENTED**
- Messaging / Chat — **IMPLEMENTED**
- Notifications — **IMPLEMENTED**
- Media access / acquisition — **IMPLEMENTED**
- Device permissions — **IMPLEMENTED**
- Data import / export / transfer — **IMPLEMENTED**
- Sync / retry / recovery / cache — **IMPLEMENTED**
- Verification / moderation / reporting — **IMPLEMENTED**
- AI assistant / tool registry — **IMPLEMENTED**
- Voice messages / audio calls / video calls — **IMPLEMENTED**
- Call signalling — **IMPLEMENTED**
- Location / geospatial capability — **IMPLEMENTED**
- Document preview / conversion — **IMPLEMENTED**
- Internationalisation / translation capability — **IMPLEMENTED**

## 5. Dashboard — Runtime Vertical Slice
- Dashboard architecture attack — **IMPLEMENTED/DOCUMENTED**
- Dashboard boundary map — **IMPLEMENTED/DOCUMENTED**
- Dashboard component blueprint — **IMPLEMENTED/DOCUMENTED**
- Dashboard implementation contract — **IMPLEMENTED/DOCUMENTED**
- Dashboard runtime vertical slice — **IMPLEMENTED**
- Dashboard runtime tests — **IMPLEMENTED**
- Dashboard runtime documentation — **IMPLEMENTED**

### Locked dashboard baseline
1. Dashboard Shell
2. Header
3. Profile
4. Navigation
5. Smart Clock
6. Ticker / Status Strip
7. Quick Actions
8. Summary / KPI Cards
9. Activity / Recent Items
10. Notifications Panel
11. Feature / Capability Cards
12. Custom Dashboard + Cards Gallery

Customisation includes hide/unhide, add/remove from dashboard, pin/unpin, reorder and reset-to-default. Dashboard component deletion is not a customisation operation.

## 6. Presentation Stack — Runtime Foundation
- Repository presentation-stack audit — **IMPLEMENTED/DOCUMENTED**
- Presentation architecture attack — **IMPLEMENTED/DOCUMENTED**
- Presentation boundary — **IMPLEMENTED/DOCUMENTED**
- Presentation blueprint — **IMPLEMENTED/DOCUMENTED**
- Presentation implementation contract — **IMPLEMENTED/DOCUMENTED / SEALED**
- Presentation implementation roadmap — **IMPLEMENTED/DOCUMENTED**
- Selected foundation: React + TypeScript + Vite + React Router + standards-based CSS/design tokens — **IMPLEMENTED**
- Presentation runtime foundation — **IMPLEMENTED**
- Dashboard runtime vertical slice — **IMPLEMENTED**

The presentation stack remains a UI foundation. Domain ownership remains in Work_Disk services/contracts. No domain database access is performed by Dashboard components.

## 7. Reusable Component System — Runtime Implementation
- Component ecosystem audit — **IMPLEMENTED/DOCUMENTED**
- Component architecture attack — **IMPLEMENTED/DOCUMENTED**
- Component boundary map — **IMPLEMENTED/DOCUMENTED / SEALED**
- Component system blueprint — **IMPLEMENTED/DOCUMENTED**
- Component system contract — **IMPLEMENTED/DOCUMENTED / SEALED**
- Component runtime foundation — **IMPLEMENTED**
- 40-component registry — **IMPLEMENTED**
- Foundation primitives including design tokens and 3D Surface — **IMPLEMENTED**
- Core UI components — **IMPLEMENTED**
- Container components — **IMPLEMENTED**
- Input/Data components — **IMPLEMENTED**
- Work_Disk specialised presentation components — **IMPLEMENTED**
- Dashboard Card infrastructure — **IMPLEMENTED**
- Registered Cards Gallery infrastructure — **IMPLEMENTED**
- Component registry invariant tests — **IMPLEMENTED**
- Component runtime CI verification — **PASS / GREEN**

### Locked component layers
- Foundation: tokens, typography, layout, responsive, motion and 3D surface primitives
- Core UI: actions, identity, feedback and basic interaction components
- Containers: cards, panels, sections, grids, stacks, dialogs and drawers
- Input/Data: inputs, selectors, search, filters, forms, lists and tables
- Work_Disk specialised: profile, capability, notification, activity, media, chat and feed components

Generic component infrastructure does not redefine Dashboard's 12 core boundaries.

## 8. Feature Surfaces — P0 Account/Profile + Workspace
- Feature surface audit and priority attack — **IMPLEMENTED/DOCUMENTED**
- Account/Profile + Workspace architecture attack — **IMPLEMENTED/DOCUMENTED**
- Account/Profile + Workspace boundary map — **IMPLEMENTED/DOCUMENTED / SEALED**
- Account/Profile + Workspace blueprint — **IMPLEMENTED/DOCUMENTED**
- Account/Profile + Workspace implementation contract — **IMPLEMENTED/DOCUMENTED / SEALED**
- Domain-neutral AccountProfileModel contract — **IMPLEMENTED**
- Workspace Shell — **IMPLEMENTED**
- Account/Profile surface — **IMPLEMENTED**
- Workspace navigation — **IMPLEMENTED**
- Dashboard integration route — **IMPLEMENTED**
- Settings destination registration — **IMPLEMENTED / FEATURE DEFERRED**
- Account/Profile + Workspace feature tests — **IMPLEMENTED**
- Web CI verification — **PASS / GREEN**

### Locked feature boundaries
1. Account Context Surface
2. Profile Surface
3. Workspace Shell
4. Workspace Navigation
5. Profile Empty State

No account/profile persistence, authentication, permission grants, or database access is owned by this presentation surface.

## 9. Documentation Areas
- Account documentation — **IMPLEMENTED**
- Profile documentation — **IMPLEMENTED**
- Tool documentation — **IMPLEMENTED**
- Master Menu — **IMPLEMENTED**
- Dashboard architecture documentation — **IMPLEMENTED**
- Dashboard runtime documentation — **IMPLEMENTED**
- Presentation stack architecture documentation — **IMPLEMENTED**
- Reusable component system documentation — **IMPLEMENTED**
- Account/Profile + Workspace feature documentation — **IMPLEMENTED**
- Profile Presentation Adapter architecture documentation — **IMPLEMENTED**

## 10. Current Audit Notes
- This menu is an inventory, not a replacement for individual architecture contracts.
- A feature must not be marked IMPLEMENTED merely because it was discussed or designed.
- Duplicate or overlapping capabilities must be resolved at the architecture/boundary level before adding another Tool-Bot.
- CI is not marked PASS unless an actual workflow run is observed.
- Dashboard runtime is implemented as a presentation vertical slice with domain-neutral typed inputs and empty states when authoritative data is unavailable.
- Dashboard personalisation never deletes a feature or its domain data.
- The presentation stack is not itself a domain authority and communicates through explicit service contracts/adapters.
- Reusable components must follow the sealed component system contract and cannot become domain authorities.
- Component runtime implementation is recorded only after PR #77 was merged to `main` and its CI verification was observed green.
- Account/Profile + Workspace runtime is recorded only after PR #78 was merged to `main` and Web workflow run #9 completed successfully.
- Settings is only registered as a workspace destination; its feature implementation remains deferred.
- Profile Presentation Adapter is recorded only after PR #80 was merged to `main` and Main Verification workflow #16 completed successfully.
- The Profile Presentation Adapter is a presentation boundary only; it does not replace or modify BOT-01/BOT-02 authority and does not claim to be the transport/application integration layer.

## 11. Update Rule
Every future addition follows:

**Architecture → Attack → Boundary → Blueprint → Contract → Roadmap → Implementation → Tests → Docs → PR → Review → Merge → Main Verification → Master Menu Update**

The Master Menu answers:

> **What does Work_Disk actually have right now?**

## 12. Change Log
### v1.8 — Profile Presentation Adapter boundary
Recorded the P0-2 domain/service contract audit, authoritative ProfileService read/assembly path, presentation adapter boundary, adapter implementation, anti-fabrication tests, architecture documentation, merged PR #80 and green Main Verification workflow #16. BOT-01 and BOT-02 boundaries remained unchanged.

### v1.7 — Account/Profile + Workspace feature surface
Recorded the P0 Account/Profile + Workspace architecture attack, five feature boundaries, blueprint, sealed contract, domain-neutral presentation model, Workspace Shell, Account/Profile surface, navigation, Dashboard route integration, deferred Settings destination, feature tests and green Web CI verification.

### v1.6 — Reusable component system runtime implementation
Recorded the merged component runtime foundation, 40-component registry, shared 3D visual foundation, reusable UI/container/input/data/specialised components, Dashboard Card/Cards Gallery infrastructure, invariant tests and green CI verification.

### v1.5 — Reusable component system boundary, blueprint and contract
Recorded the component ecosystem audit, architecture attack, 40-component boundary map across five layers, blueprint and sealed contract.

### v1.4 — Dashboard runtime vertical slice
Recorded the implemented Dashboard runtime, twelve locked component boundaries, non-destructive customisation, Cards Gallery, tests and runtime documentation.

### v1.3 — Presentation boundary, blueprint, contract and roadmap
Recorded the presentation boundary, implementation blueprint, sealed contract and incremental roadmap.

### v1.2 — Presentation stack architecture phase
Recorded the repository presentation-stack audit and the selected React + TypeScript + Vite + React Router foundation.

### v1.1 — Dashboard architecture phase
Added the attacked 12-component dashboard baseline, boundaries, blueprint and contract.

### v1.0 — Initial Master Menu
Created after repository audit of the current `work_disk_web` structure and current Tool-Bot inventory.
