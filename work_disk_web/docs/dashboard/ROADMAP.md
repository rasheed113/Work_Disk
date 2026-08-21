# Dashboard Implementation Roadmap

## Gate 1 — Architecture / Attack
Complete. Twelve core boundaries survived attack.

## Gate 2 — Boundary / Blueprint
Complete. Ownership, dependency direction, registry and customisation boundaries are defined.

## Gate 3 — Contract
Complete. Dashboard invariants and non-goals are sealed in `IMPLEMENTATION_CONTRACT.md`.

## Gate 4 — Implementation
Implement the component contracts in repository-native code after confirming the existing web presentation/runtime stack. Do not invent a framework or replace the current architecture merely to satisfy the dashboard.

## Gate 5 — Tests
Contract tests must cover visibility, unhide, add/remove, pin/unpin, ordering, reset, eligibility, context isolation, stale preferences and non-destructive behaviour.

## Gate 6 — Documentation
Update dashboard architecture and component documentation with actual implementation paths and verification evidence.

## Gate 7 — PR / Review / Merge
Open a dedicated PR, inspect the full diff, perform review, merge only when the contract is satisfied.

## Gate 8 — Main Verification / Master Menu
Verify the merged state on `main`, then update `docs/MASTER_MENU.md` to reflect the dashboard's actual implementation status.

## Current state
Architecture, attack, boundary, blueprint and contract are complete. Runtime implementation is intentionally not claimed until the repository's actual web presentation stack is identified and implemented against it.
