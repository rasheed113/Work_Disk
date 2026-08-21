# Work_Disk Web — Tools — BOT-04
# Delete Bot — Implementation Roadmap

## Phase 1 — Architecture Reconciliation

- [x] Preserve Delete Bot as an action-owning Tool Bot.
- [x] Replace immediate-only semantics with Normal + Approval-Gated execution modes.
- [x] Remove the need for a separate Freeze Bot from this lifecycle.
- [x] Define hold as operation state, not target deletion state.
- [x] Define approval acceptance as commit permission, not deletion success.
- [x] Define rejection as release without reconstruction.
- [x] Keep Warning & Approval Bot responsible only for warning/approval decision.

## Phase 2 — Public Contract

- [x] Add execution mode to the deletion request.
- [x] Add approval decision state.
- [x] Require approval evidence when applying a positive or negative decision.
- [x] Add pending/rejected public results.
- [x] Keep normal deletion backward-compatible at the semantic level.

## Phase 3 — Lifecycle Boundaries

- [x] Add Warning & Approval boundary.
- [x] Add pending-operation persistence boundary.
- [x] Hold approval-required deletion before destructive execution.
- [x] Commit only after authoritative approval.
- [x] Release on rejection.
- [x] Keep approved pending state on authoritative execution failure.
- [x] Introduce no expiry.

## Phase 4 — Verification

- [x] Normal delete path.
- [x] Approval pending path.
- [x] Approval accepted path.
- [x] Approval rejected path.
- [x] Duplicate pending request protection.
- [x] Missing evidence protection.
- [x] Approval failure protection.
- [x] Execution failure protection.
- [x] Authority boundary protection.

## Phase 5 — Documentation

- [x] Update BLUEPRINT.md.
- [x] Update IMPLEMENTATION_CONTRACT.md.
- [x] Update README.md.
- [x] Update PROFILE.md.
- [x] Update ROADMAP.md.

## Phase 6 — Repository Gate

- [ ] Run all repository tests.
- [ ] Run `git diff --check`.
- [ ] Inspect final BOT-04 diff for unrelated changes.
- [ ] Commit the complete BOT-04 modification.
- [ ] Push the feature branch.
- [ ] Open a reviewable PR.
