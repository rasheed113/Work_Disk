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

## 5. Dashboard — Architecture Phase
- Dashboard architecture attack — **DESIGNED**
- Dashboard boundary map — **DESIGNED**
- Dashboard component blueprint — **DESIGNED**
- Dashboard implementation contract — **DESIGNED**
- Dashboard implementation/tests — **PLANNED**

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

## 6. Presentation Stack — Architecture & Contract Phase
- Repository presentation-stack audit — **DESIGNED**
- Presentation architecture attack — **DESIGNED**
- Presentation boundary — **DESIGNED**
- Presentation blueprint — **DESIGNED**
- Presentation implementation contract — **DESIGNED / SEALED**
- Presentation implementation roadmap — **DESIGNED**
- Selected foundation: React + TypeScript + Vite + React Router + standards-based CSS/design tokens — **DESIGNED**
- Presentation runtime implementation — **PLANNED**

The selected presentation stack is a UI foundation only. Domain ownership remains in Work_Disk services/contracts. Runtime implementation is not claimed until the presentation implementation gates are completed.

## 7. Documentation Areas
- Account documentation — **IMPLEMENTED**
- Profile documentation — **IMPLEMENTED**
- Tool documentation — **IMPLEMENTED**
- Master Menu — **IMPLEMENTED**
- Dashboard architecture documentation — **DESIGNED**
- Presentation stack architecture documentation — **DESIGNED**

## 8. Current Audit Notes
- This menu is an inventory, not a replacement for individual architecture contracts.
- A feature must not be marked IMPLEMENTED merely because it was discussed or designed.
- Duplicate or overlapping capabilities must be resolved at the architecture/boundary level before adding another Tool-Bot.
- CI is not marked PASS unless an actual workflow run is observed.
- Runtime dashboard implementation is not claimed until the repository's actual web presentation stack is implemented and verified.
- The presentation stack is not itself a domain authority and must communicate through explicit service contracts/adapters.

## 9. Update Rule
Every future addition follows:

**Architecture → Attack → Boundary → Blueprint → Contract → Roadmap → Implementation → Tests → Docs → PR → Review → Merge → Main Verification → Master Menu Update**

The Master Menu answers:

> **What does Work_Disk actually have right now?**

## 10. Change Log
### v1.3 — Presentation boundary, blueprint, contract and roadmap
Recorded the presentation boundary, implementation blueprint, sealed contract and incremental roadmap. Runtime implementation remains explicitly unclaimed.

### v1.2 — Presentation stack architecture phase
Recorded the repository presentation-stack audit and the selected React + TypeScript + Vite + React Router foundation.

### v1.1 — Dashboard architecture phase
Added the attacked 12-component dashboard baseline, boundaries, blueprint and contract.

### v1.0 — Initial Master Menu
Created after repository audit of the current `work_disk_web` structure and current Tool-Bot inventory.
