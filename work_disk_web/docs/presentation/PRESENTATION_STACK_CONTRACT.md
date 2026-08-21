# Work_Disk Web Presentation Stack — Implementation Contract

## Status
CONTRACT SEALED — governs presentation-stack implementation.

## Purpose

Define the non-negotiable implementation contract for the Work_Disk Web presentation layer selected as React + TypeScript + Vite + React Router with standards-based CSS/design tokens.

## Contract Rules

### PSC-01 — Presentation Non-Authority
Presentation code SHALL NOT become authoritative for identity, capabilities, permissions, domain records, notifications, media ownership, reconciliation, or persistence.

### PSC-02 — Explicit Integration
Components SHALL consume domain/service information through explicit typed contracts or adapters. Direct database or domain-storage access from presentation code is prohibited.

### PSC-03 — Replaceability
The presentation layer SHALL be replaceable without rewriting authoritative domain logic.

### PSC-04 — Route Separation
Routing SHALL control page/layout composition only. Authorization and capability authority SHALL remain in service/domain contracts.

### PSC-05 — State Classification
Implementation SHALL distinguish ephemeral interaction state, service-derived view state, and presentation preferences. Presentation preference changes SHALL NOT mutate authoritative domain records unless an explicit domain contract says so.

### PSC-06 — Dashboard Non-Destruction
Hide/unhide, add/remove from Dashboard, pin/unpin, reorder, and reset-to-default SHALL operate on presentation preferences. Dashboard customisation SHALL NOT delete domain features or records.

### PSC-07 — Cards Gallery Eligibility
Cards Gallery SHALL expose only registered and eligible presentation components. It SHALL NOT manufacture capabilities or imply permissions that the authoritative service layer has not granted.

### PSC-08 — Context Preservation
Context changes in the UI SHALL NOT destructively erase, overwrite, or conceal authoritative data belonging to another context.

### PSC-09 — Responsive Equivalence
Responsive layouts MAY change presentation, but SHALL preserve the same domain semantics and service contracts.

### PSC-10 — Accessibility
Interactive presentation components SHALL provide keyboard-operable and semantically appropriate controls and shall not encode accessibility as an optional afterthought.

### PSC-11 — Test Integrity
Tests SHALL verify real presentation behaviour and contract boundaries. Hardcoded test outcomes, fake production services, and fixture-driven claims of real domain behaviour are prohibited.

### PSC-12 — No Premature Abstraction
Components SHALL be extracted as shared components only when their boundary is genuinely reusable. Duplication shall not be eliminated by creating speculative framework abstractions.

### PSC-13 — Design Tokens
Shared visual decisions SHALL use the design-token/CSS layer rather than scattered component-specific constants where a shared semantic token exists.

### PSC-14 — Error and Loading Integrity
Loading, empty, error, unavailable, and permission-denied states SHALL remain distinguishable and SHALL NOT be represented as fabricated successful domain outcomes.

### PSC-15 — Incremental Vertical Slices
Implementation SHALL proceed in verifiable vertical slices, with tests and documentation for each completed slice before declaring it implemented.

## Acceptance Gate

A presentation-stack implementation is complete only when its implemented slice passes code review, tests, documentation, PR merge, and main-branch verification under the Work_Disk development workflow.

## Traceability

This contract implements the selected presentation-stack architecture and boundary blueprint. It does not alter Work_Disk core/domain authority rules.
