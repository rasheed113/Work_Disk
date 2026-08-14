# Work_Disk Web — Account — Bot 01
# Implementation Contract

## 1. Purpose

This contract converts the current Work_Disk Web Account architecture
into the minimum concrete requirements needed to implement Bot 01.

This is a build document, not an independent architecture.

## 2. Fresh Project Boundary

This contract is written for the current Work_Disk Web project.

The following are explicitly NOT implementation sources:

- previous Work_Disk code;
- previous Work_Disk database designs;
- previous security architectures;
- previous law numbering;
- previous validation pipelines;
- previous implementation contracts;
- previous Bot implementations.

## 3. Bot Scope

Bot 01 implements only the Account scope approved by the current
architecture.

Anything not required by the current Account scope remains outside Bot 01.

## 4. Implementation Areas

The implementation may use:

src/account/bot-01/models/
src/account/bot-01/repositories/
src/account/bot-01/services/
src/account/bot-01/utils/
src/account/bot-01/validators/

Tests belong under:

tests/account/bot-01/unit/
tests/account/bot-01/integration/

## 5. Data Model

Account data structures must be created only from the current Account
architecture.

No field, state, relationship, identifier, or lifecycle rule may be
invented merely for implementation convenience.

If the architecture has not yet defined a detail, implementation must
not silently turn an assumption into an architectural rule.

## 6. Service Boundary

Services must expose only operations required by the Account contract.

Business rules belong in the appropriate domain/service boundary rather
than being scattered through repositories or transport code.

## 7. Repository Boundary

Repositories are responsible for persistence interaction required by the
Account implementation.

They must not redefine Account business rules or architectural ownership.

## 8. Validator Boundary

Validators may enforce requirements explicitly defined by the current
Account contract.

They must not introduce an independent authorization or security
architecture.

## 9. Persistence

The persistence technology and exact schema must follow the current
project architecture when defined.

Until those decisions are explicitly established, implementation must
not import an older database design.

## 10. Errors

Errors must be deterministic and must distinguish failed operations from
successful operations.

Exact error codes, transport mappings, and external representations are
defined only when required by the current contract.

## 11. Tests

Bot 01 must contain tests for every implemented Account behaviour.

Tests must cover:

- valid behaviour;
- invalid input;
- boundary conditions;
- failure behaviour;
- ownership/data integrity where applicable;
- repository/service interaction where applicable.

Tests must verify actual project requirements rather than historical
Work_Disk behaviour.

## 12. Implementation Rule

When the implementation encounters an architectural decision that has
not yet been defined:

STOP THAT DECISION.

Do not guess.
Do not copy the old project.
Do not create a new architectural rule inside code.

Record the missing decision and return to the architecture.

## 13. Completion

The contract is satisfied when the approved Account scope is implemented
and tested without exceeding the Bot 01 boundary.

The purpose of this document is to enable project building, not to create
unnecessary documentation.
