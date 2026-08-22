# Work_Disk — Master Menu

> Living inventory of what Work_Disk actually contains. This document is updated only after a change is implemented, reviewed, merged, and verified on `main`.

## Status Rules
- **IMPLEMENTED** — present on `main` and verified.
- **DESIGNED** — architecture/contract exists, implementation is not yet verified on `main`.
- **IN PROGRESS** — active implementation work.
- **DEFERRED** — intentionally postponed by architecture decision.
- **CANDIDATE** — under audit; not part of the implemented inventory.

## Reusable Page Properties
- Page-property architecture/role boundary — **IMPLEMENTED/DOCUMENTED**
- Page-property contract — **IMPLEMENTED/DOCUMENTED / SEALED**
- Reusable page-property registry — **IMPLEMENTED**
- Page-property invariant tests — **IMPLEMENTED / CI VERIFICATION PENDING**

### Locked page-property rule
Page properties are presentation declarations only. They map reusable properties to existing authoritative Tool-Bot capabilities. Role/capability/permission authority decides whether a property is usable in the current context. Pages do not own BOT authority or business logic. Missing/unavailable capability is never replaced by fake UI behaviour.

## Real-Time Web Transport — Current Foundation
- Shared Web transport architecture boundary — **DESIGNED**
- Provider-neutral TypeScript transport interface — **IMPLEMENTED / TYPECHECK GREEN**
- HTTP Web Transport Provider BOT — **IMPLEMENTED / TYPECHECK GREEN**
- Profile endpoint contract — **IMPLEMENTED/DOCUMENTED**
- Profile C++ endpoint handler boundary — **IMPLEMENTED / RUNTIME BINDING PENDING**
- HTTP route infrastructure boundary — **IMPLEMENTED / NETWORK LISTENER PENDING**
- Concrete network HTTP listener + JSON codec — **PENDING**
- End-to-end Profile HTTP verification — **PENDING**

## Update Rule
Every future addition follows:

**Architecture → Attack → Boundary → Blueprint → Contract → Roadmap → Implementation → Tests → Docs → PR → Review → Merge → Main Verification → Master Menu Update**

## Change Log
### v2.1 — Reusable Page Properties
Recorded the reusable page-property contract, role/capability boundary, registry, invariant tests and Master Menu registration. Properties reuse existing Tool-Bot authority and never become page-local business logic.

### v2.0 — Real-Time Web Transport
Recorded the shared transport boundary, provider-neutral TypeScript transport and HTTP provider foundation. Concrete network runtime remains pending until the actual listener, JSON codec and end-to-end verification exist.
