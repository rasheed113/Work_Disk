# BOT-06 Archive 📦 — Roadmap

## Phase 1 — Architecture
- [x] Define domain-neutral purpose
- [x] Separate Archive from Delete/Trash
- [x] Define multi-caller boundary
- [x] Attack and resolve lifecycle/security edge cases

## Phase 2 — Contract
- [x] Public command/result model
- [x] Authority boundary
- [x] Durable lifecycle boundary
- [x] Opaque source reference
- [x] Idempotency/version requirements

## Phase 3 — Implementation
- [x] Public C++ types
- [x] Public interfaces
- [x] Boundary orchestration
- [ ] Native repository build integration

## Phase 4 — Verification
- [x] Contract test source
- [ ] CI compilation
- [ ] Full repository integration tests
- [ ] Domain-specific integration verification

## Phase 5 — Integration
- [ ] Inbox caller
- [ ] Chat caller
- [ ] Post caller
- [ ] Notification caller
- [ ] Document caller
- [ ] Other domain callers

CI/compiler work is intentionally deferred to the later build phase.
