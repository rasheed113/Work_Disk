# Work_Disk Web — BOT-05 Evidence Verification Bot
# Implementation Roadmap

## Phase 1 — Architecture Translation

- Translate the evidence architecture into explicit data and dependency boundaries.
- Preserve `Evidence Signer ≠ Execution Authority ≠ State Authority`.
- Preserve `State → Evidence, never Evidence → State`.
- Keep authenticity, completeness, freshness, purpose, context, and consumability independent.

## Phase 2 — Verification Core

- Implement evidence and authority tuple models.
- Implement structural validator.
- Implement signature-verification dependency.
- Implement signer historical/current authorization dependency.
- Implement canonical lineage dependency.
- Implement purpose and coverage checks.
- Implement optional freshness/current-authority checks.
- Implement optional single-use consumption boundary.

## Phase 3 — Attack-to-Code Mapping

- 12A–12F → signature, lineage, coverage, freshness, context, purpose, consumability.
- 13A–13D → canonical state dependency; no recovery authority creation.
- 14A–14B-F → no arrival-order, popularity, relay, or local-view authority.
- 14C → no partition reconciliation authority inside evidence verification.

## Phase 4 — Verification

- Run unit contract tests.
- Run integration boundary test.
- Compile with C++17 and strict warnings.
- Confirm historical evidence survives signer revocation when current authority is not requested.
- Confirm current-authority verification fails without freshness/canonical current state.
- Confirm single-use replay is rejected only when the evidence is explicitly single-use.

## Phase 5 — Repository Completion

- Add README, PROFILE, and COMPLETION record.
- Inspect implementation paths and boundaries.
- Commit as one BOT-05 implementation change.
- Push the feature branch.

## Phase 6 — Future Integration

Production integration must supply:

- a real cryptographic signature verifier;
- a real signer/key registry;
- a real authoritative canonical state/lineage view;
- a durable atomic consumption store where single-use semantics are required.

These are dependencies, not responsibilities to be silently absorbed by BOT-05.
