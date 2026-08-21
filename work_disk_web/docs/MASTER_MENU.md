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
- BOT-01 — Account Authentication Foundation — **IMPLEMENTED**
- BOT-02 — Profile Authority & Assembly — **IMPLEMENTED**
- BOT-03 — Public Identifier — **IMPLEMENTED**
- BOT-04 — Delete Tool — **IMPLEMENTED**
- BOT-05 — Trash Tool — **IMPLEMENTED**
- BOT-06 — Archive Tool — **IMPLEMENTED**
- BOT-07 — Edit Tool — **IMPLEMENTED**
- BOT-08 — Search Tool — **IMPLEMENTED**
- BOT-09 — Mark / Unmark Tool — **IMPLEMENTED**
- BOT-10 — Filter Tool — **IMPLEMENTED**
- BOT-11 — Sort By Tool — **IMPLEMENTED**
- BOT-12 — Action Tool / Action Board — **IMPLEMENTED**
- BOT-13 — Content / Post Tool — **IMPLEMENTED**
- BOT-14 — Relationship Tool — **IMPLEMENTED**
- BOT-15 — Media / Attachment Tool — **IMPLEMENTED**
- BOT-16 — Notification Tool — **IMPLEMENTED**
- BOT-17 — Messaging Tool — **IMPLEMENTED**
- BOT-18 — Reaction Tool — **IMPLEMENTED**
- BOT-19 — Comment / Reply Tool — **IMPLEMENTED**
- BOT-20 — Share / Repost Tool — **IMPLEMENTED**
- BOT-21 — Save / Bookmark Tool — **IMPLEMENTED**
- BOT-22 — Feed Tool — **IMPLEMENTED**
- BOT-23 — Report Tool — **IMPLEMENTED**
- BOT-24 — Block / Mute Tool — **IMPLEMENTED**
- BOT-25 — Moderation Tool — **IMPLEMENTED**
- BOT-26 — Discovery Tool — **IMPLEMENTED**
- BOT-27 — Groups / Community Tool — **IMPLEMENTED**
- BOT-28 — Service Request / Intake Tool — **IMPLEMENTED**
- BOT-29 — Verification Tool — **IMPLEMENTED**
- BOT-30 — Document / Records Tool — **IMPLEMENTED**
- BOT-31 — Case Workflow Tool — **IMPLEMENTED**
- BOT-32 — Queue / Scheduler Tool — **IMPLEMENTED**
- BOT-33 — Audit Trail Tool — **IMPLEMENTED**
- BOT-34 — Search Index Tool — **IMPLEMENTED**
- BOT-35 — Validation Tool — **IMPLEMENTED**
- BOT-36 — Notification Tool — **IMPLEMENTED**
- BOT-37 — Media Access Tool — **IMPLEMENTED**
- BOT-38 — Permission Tool — **IMPLEMENTED**
- BOT-39 — Data Sync Tool — **IMPLEMENTED**
- BOT-40 — Retry / Recovery Tool — **IMPLEMENTED**
- BOT-41 — Cache Tool — **IMPLEMENTED**
- BOT-42 — Export Tool — **IMPLEMENTED**
- BOT-43 — Import Tool — **IMPLEMENTED**
- BOT-44 — Relationship Tool — **IMPLEMENTED**
- BOT-45 — Feed Tool — **IMPLEMENTED**
- BOT-46 — Chat Tool — **IMPLEMENTED**
- BOT-47 — File Transfer Tool — **IMPLEMENTED**
- BOT-48 — Presence Tool — **IMPLEMENTED**
- BOT-49 — AI Assistant Tool — **IMPLEMENTED**
- BOT-50 — Tool Registry / Dispatcher — **IMPLEMENTED**
- BOT-51 — Device Access Tool — **IMPLEMENTED**
- BOT-52 — Media Acquisition Tool — **IMPLEMENTED**
- BOT-53 — QR Tool — **IMPLEMENTED**
- BOT-54 — i18n / Translation Tool — **IMPLEMENTED**
- BOT-55 — Voice Message Tool — **IMPLEMENTED**
- BOT-56 — Audio Call Tool — **IMPLEMENTED**
- BOT-57 — Video Call Tool — **IMPLEMENTED**
- BOT-58 — Call Signalling Tool — **IMPLEMENTED**
- BOT-59 — Location & Geospatial Tool — **IMPLEMENTED**
- BOT-60 — Document Preview / Conversion Tool — **IMPLEMENTED**

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

## 6. Documentation Areas
- Account documentation — **IMPLEMENTED**
- Profile documentation — **IMPLEMENTED**
- Tool documentation — **IMPLEMENTED**
- Master Menu — **IMPLEMENTED**
- Dashboard architecture documentation — **DESIGNED**

## 7. Current Audit Notes
- This menu is an inventory, not a replacement for individual architecture contracts.
- A feature must not be marked IMPLEMENTED merely because it was discussed or designed.
- Duplicate or overlapping capabilities must be resolved at the architecture/boundary level before adding another Tool-Bot.
- CI is not marked PASS unless an actual workflow run is observed.
- Runtime dashboard implementation is not claimed until the repository's actual web presentation stack is identified and implemented against it.

## 8. Update Rule
Every future addition follows:

**Architecture → Attack → Boundary → Blueprint → Contract → Roadmap → Implementation → Tests → Docs → PR → Review → Merge → Main Verification → Master Menu Update**

The Master Menu answers:

> **What does Work_Disk actually have right now?**

## 9. Change Log
### v1.1 — Dashboard architecture phase
Added the attacked 12-component dashboard baseline, boundaries, blueprint and contract. Runtime implementation remains explicitly unclaimed until the repository presentation stack is identified and the implementation/test gates are completed.

### v1.0 — Initial Master Menu
Created after repository audit of the current `work_disk_web` structure and current Tool-Bot inventory.
