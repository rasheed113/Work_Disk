# Work_Disk Web — Account — Bot 01 Blueprint

## Status

DESIGN PHASE

Implementation has NOT started.

## 1. Purpose

This document defines the implementation boundary for Account Bot 01.

Bot 01 exists to establish the first clean implementation unit of the
Work_Disk Web Account domain.

It must remain bounded, deterministic, testable, and traceable to the
sealed architecture.

## 2. Architectural Principle

The Account is the stable identity boundary.

Account is NOT a Dashboard Type.

Roles, capabilities, relationships, permissions, and contextual
presentation exist around the Account without destroying or replacing
the underlying Account identity.

## 3. Core Account Model

The authoritative conceptual relationship is:

Account
    ↓
Roles
    ↓
Capabilities
    ↓
Relationships
    ↓
Permissions
    ↓
Current Context
    ↓
Dynamic Dashboard

The Account remains stable while contextual authority changes.

## 4. Data Ownership Rule

Changing role or execution context MUST NOT:

- delete another role's data,
- overwrite another role's data,
- destructively hide another role's data,
- transfer ownership of Account-level data.

Context switching changes the active execution context.

It does not rewrite the underlying Account.

## 5. Capability Lifecycle

Persistent capability lifecycle states are:

- AVAILABLE
- ENABLED
- SUSPENDED
- REVOKED

ACTIVE is NOT a persistent capability state.

ACTIVE belongs to the current execution context.

## 6. Account-Level Data

Account-level data belongs to the Account itself.

Examples include Account-global information and personal structures
whose ownership is independent of a selected role.

Role-specific data must remain associated with its appropriate
role/capability/relationship boundary.

## 7. Bot Boundary

Bot 01 MUST define and implement only the Account responsibilities
explicitly assigned by the final approved contract.

It MUST NOT independently invent:

- new Account types,
- authorization rules,
- capability rules,
- delegation authority,
- transport authority,
- canonical recovery authority,
- security bypasses,
- Dashboard authority.

## 8. Identity Boundary

Account identity and execution identity are separate concepts.

Principal identity represents the originating authority subject.

Execution identity represents the actor/service currently executing
within an authorized context.

A delegated execution identity MUST NOT automatically inherit
unauthorized authority from the principal.

## 9. Security Binding

Where Account data participates in security-sensitive mutations,
the implementation must respect the sealed AuthorityContext contract.

The relevant authority context includes:

- PrincipalID
- ExecutionID
- Audience
- CapabilitySet
- ResourceScope
- Generation
- Epoch
- Anchor
- Protocol identity/version/digest
- Delegation lineage
- Validity bound
- Challenge nonce

The implementation must never treat an isolated identifier as complete
authority.

## 10. Persistence Principle

Storage is a substrate.

SQLite does not become the architectural source of authority merely
because it stores Account state.

Domain logic remains responsible for enforcing the architectural
invariants.

Database constraints may strengthen enforcement but must not redefine
the architecture.

## 11. Failure Principle

Security-sensitive failures must fail closed.

No implementation may silently:

- substitute identity,
- broaden capability,
- repair invalid authority,
- resurrect revoked state,
- ignore generation fences,
- bypass validation,
- manufacture canonical authority.

## 12. Source Traceability

Every implementation element must identify its authoritative source.

Required mapping format:

| Implementation Element | Authoritative Source | Status |
|---|---|---|
| Account identity boundary | Step 1 / Account Architecture | REQUIRED |
| Role separation | Step 4 / Account Architecture | REQUIRED |
| Capability lifecycle | Sealed Capability Architecture | REQUIRED |
| Context separation | Account Architecture | REQUIRED |
| Security context binding | Law #37.13 / Phase 3 ACC | REQUIRED |
| Delegated execution boundary | Law #37.14 | REQUIRED |
| Persistence enforcement | Phase 2 Database Contract | REQUIRED |

If any required source is unavailable or ambiguous:

> STOP CODE GENERATION.

## 13. Implementation Gate

Before writing production code, Bot 01 must have:

1. final responsibility boundary,
2. data model contract,
3. interface contract,
4. persistence contract,
5. error contract,
6. invariant mapping,
7. mandatory test specification,
8. source traceability.

Only after these are approved may implementation begin.

## 14. Test Philosophy

Tests must verify behaviour against architectural invariants.

A test that merely confirms that code executes successfully is
insufficient.

Tests must also prove that forbidden operations fail.

Examples:

- context switching does not destroy unrelated data,
- unauthorized capability is rejected,
- revoked capability cannot execute,
- execution identity cannot silently inherit authority,
- Account identity remains stable,
- invalid security context fails closed.

## 15. Completion Rule

Bot 01 is complete only when its implementation and tests satisfy this
blueprint and every implementation element has an authoritative source.

Architecture remains superior to implementation.

