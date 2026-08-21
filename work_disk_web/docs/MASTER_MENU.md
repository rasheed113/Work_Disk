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

## 7. Documentation Areas
- Account documentation — **IMPLEMENTED**
- Profile documentation — **IMPLEMENTED**
- Tool documentation — **IMPLEMENTED**
- Master Menu — **IMPLEMENTED**
- Dashboard architecture documentation — **IMPLEMENTED**
- Dashboard runtime documentation — **IMPLEMENTED**
- Presentation stack architecture documentation — **IMPLEMENTED**

## 8. Current Audit Notes
- This menu is an inventory, not a replacement for individual architecture contracts.
- A feature must not be marked IMPLEMENTED merely because it was discussed or designed.
- Duplicate or overlapping capabilities must be resolved at the architecture/boundary level before adding another Tool-Bot.
- CI is not marked PASS unless an actual workflow run is observed.
- Dashboard runtime is implemented as a presentation vertical slice with domain-neutral typed inputs and empty states when authoritative data is unavailable.
- Dashboard personalisation never deletes a feature or its domain data.
- The presentation stack is not itself a domain authority and communicates through explicit service contracts/adapters.

## 9. Update Rule
Every future addition follows:

**Architecture → Attack → Boundary → Blueprint → Contract → Roadmap → Implementation → Tests → Docs → PR → Review → Merge → Main Verification → Master Menu Update**

The Master Menu answers:

> **What does Work_Disk actually have right now?**

## 10. Change Log
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
