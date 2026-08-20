# Work_Disk Web — BOT-05 Evidence Verification Bot

## 1. Identity

**Bot:** BOT-05  
**Name:** Evidence Verification Bot  
**Path:** `src/evidence/bot-05/`  
**Domain:** Evidence / Observation / Verification  
**Role:** Strict evidence verification boundary

## 2. Governing Principle

> Evidence Signer ≠ Execution Authority ≠ State Authority.

> State → Evidence. Never Evidence → State.

A receipt can describe or prove an authoritative transition, but the receipt
issuer cannot create that transition merely by signing it.

## 3. Scope

BOT-05 verifies an evidence artifact against:

- cryptographic signature verification supplied by an external verifier;
- signer eligibility at the evidence epoch;
- canonical lineage membership supplied by the authoritative state layer;
- subject/resource/context binding;
- declared evidence purpose;
- declared coverage;
- optional current-authority/freshness requirements;
- optional single-use consumability.

BOT-05 does not create state, execute domain mutations, mint authority, or
choose a canonical branch.

## 4. Authority Directionality

The authoritative state layer is the source of canonicality. BOT-05 can only
return an authoritative verification result when the supplied evidence points
to an already verified canonical lineage position.

A valid signer signature proves authorship/integrity of the evidence artifact;
it does not prove that the claimed state is canonical.

## 5. Evidence Properties Are Independent

BOT-05 keeps these properties separate:

1. **Authenticity** — signature and signer eligibility.
2. **Lineage** — canonical membership and anchor.
3. **Completeness** — declared coverage satisfies the requested claim.
4. **Freshness** — only required for claims that explicitly need current state.
5. **Context binding** — subject/resource/context/domain match.
6. **Purpose** — observation, execution proof, current authority, or consumable token.
7. **Consumability** — reusable unless the contract explicitly declares single-use.

Historical evidence can remain valid even when it is no longer current authority.

## 6. Recovery / Replication / Dissemination Boundary

BOT-05 never promotes a recovery checkpoint, replica state, gossip message, relay
claim, or witness signature directly into authority. Such artifacts must first
be independently anchored to canonical state.

Arrival order, peer count, local majority, signer popularity, and relay choice
have no canonical meaning.

## 7. Conflict Rule

Conflicting state roots or unresolved lineage collisions do not create parallel
authorities. The canonical state layer decides the authoritative branch.
BOT-05 preserves verification outcomes without rewriting historical evidence.

## 8. Reconciliation Rule

Recovery may identify historical state; it may not originate authority.
Replication may preserve history; it may not manufacture authority.
Propagation may transport authority; it may not define authority.

## 9. Single-Use Rule

Single-use consumability applies only when the evidence contract explicitly
sets `SingleUse` and the caller supplies an approved consumption boundary.
Reusable evidence is never consumed merely because it was verified.

## 10. External Cryptography Boundary

BOT-05 deliberately does not implement a cryptographic primitive. The
`SignatureVerifier` boundary is responsible for real cryptographic verification.
The BOT-05 test suite uses deterministic test doubles only.

## 11. Non-Responsibilities

BOT-05 does not:

- execute transactions;
- mutate authoritative state;
- grant/revoke authority;
- decide consensus;
- create signatures or signing keys;
- choose winners using peer count or arrival order;
- perform external physical side effects;
- reverse irreversible side effects;
- replace the authoritative ledger;
- delete evidence because it is non-canonical;
- silently elevate partial evidence;
- turn historical truth into current authority without an explicit freshness check.

## 12. Attack Coverage Baseline

The approved attack work through Attack #14 is represented by these implementation
constraints:

- 12A–12F: evidence substitution, forgery, divergence, partial masquerading,
  replay/consumability, and verification confusion;
- 13A–13D: crash recovery, stale snapshots, replica reconstitution, recovery
  authority injection/equivocation;
- 14A–14B-F: stale gossip, conflicting roots, popularity/majority illusion,
  first-seen capture, withheld revocation, and Byzantine relay equivocation;
- 14C: partitioned execution reconciliation remains an upstream state/execution
  architecture concern. BOT-05 must not invent reconciliation authority.

## 13. STOP Rule

If implementation requires BOT-05 to decide an architectural question not defined
by the approved architecture and contract:

> STOP — do not guess. Return to architecture.
