# Work_Disk Web — BOT-05 Profile

## Identity

**Bot:** BOT-05  
**Name:** Evidence Verification Bot  
**Domain:** Evidence / Observation / Verification  
**Path:** `src/evidence/bot-05/`

## Governing Principle

> Evidence Signer ≠ Execution Authority ≠ State Authority.

> State → Evidence. Never Evidence → State.

## Primary Responsibility

BOT-05 verifies evidence against an independently supplied canonical state
lineage and the exact claim/scope requested by the verifier.

## Authority Model

BOT-05 has no authority-origin capability. It cannot create, grant, revoke,
execute, or mutate authoritative state.

## Key Safety Properties

- valid signature does not establish canonicality;
- historical evidence may remain valid after current authorization changes;
- partial evidence cannot satisfy a broader claim;
- purpose cannot be silently elevated;
- current authority requires explicit freshness/current-state checks;
- reusable evidence is not automatically single-use;
- single-use evidence requires an explicit consumption boundary;
- non-canonical evidence is not destroyed by verification failure.

## Dependencies

BOT-05 depends on external implementations of:

- `SignatureVerifier`;
- `SignerRegistry`;
- `CanonicalStateView`;
- optional `ConsumptionStore`.

## Verification Surface

The implementation includes standalone unit contract verification and an
integration verification of canonical state binding.

## Boundary Rule

If a future change requires BOT-05 to originate authority or choose canonical
state, STOP and return to architecture.
