# Work_Disk Web — BOT-05 Evidence Verification Bot
# Implementation Contract

## 1. Implementation Authority

Implementation follows only:

1. approved Work_Disk architecture;
2. BOT-05 `BLUEPRINT.md`;
3. this `IMPLEMENTATION_CONTRACT.md`.

No legacy evidence implementation or undocumented security assumption may be
imported.

## 2. Implementation Structure

Implementation belongs under:

`src/evidence/bot-05/`

with responsibility separation:

- `models/` — immutable evidence and verification data shapes;
- `validators/` — structural, coverage, purpose, and context validation;
- `services/` — verification boundaries and consumability support.

Tests belong under:

`tests/evidence/bot-05/`

with `unit/` and `integration/`.

## 3. State Authority Boundary

`CanonicalStateView` is read-only from BOT-05's perspective.

It must answer whether an evidence authority tuple:

- belongs to canonical lineage;
- is current;
- is superseded;
- has a freshness certificate;
- maps to the current canonical root.

BOT-05 never writes canonical state.

## 4. Signer Boundary

`SignerRegistry` must distinguish historical eligibility from current
authorization.

A signer revoked after issuance does not automatically invalidate historical
evidence. Current-authority claims must additionally require current signer
authorization.

## 5. Signature Boundary

`SignatureVerifier` is an external cryptographic dependency. BOT-05 consumes
its boolean result and never treats a valid signature as canonicality.

## 6. Evidence Verification Order

The verifier must enforce this order:

1. structural validity;
2. signature validity;
3. signer eligibility at evidence epoch;
4. requested domain/subject/resource/context binding;
5. requested purpose;
6. required coverage;
7. canonical lineage membership;
8. optional current-authority/freshness checks;
9. optional single-use consumption.

A failed gate returns a non-authoritative result and must not proceed to a
later authority-bearing operation.

## 7. Coverage Contract

Coverage is monotonic:

`OutcomeOnly < TransactionLineage < FullTransactionWithConstraints`.

A verifier must reject an evidence artifact whose declared coverage cannot
support the requested claim.

Truthful but incomplete evidence is therefore not sufficient evidence.

## 8. Freshness Contract

Freshness is not required for every historical observation.

When `require_current_authority` is false, a valid historical artifact may
remain authoritative for its historical claim after state evolution or signer
revocation.

When `require_current_authority` is true, current signer authorization,
non-supersession, freshness certification, and current canonical position are
all required.

## 9. Purpose Contract

A receipt's purpose is part of its verification boundary. An observation proof
cannot be promoted to mutation authority by interpretation alone.

## 10. Consumability Contract

Reusable evidence remains reusable.

Single-use evidence requires an explicit `ConsumptionStore` and an explicit
`consume_if_single_use` request. Consumption must be atomic at the persistence
implementation boundary; the included in-memory store is only a deterministic
test/reference implementation.

## 11. Conflict Contract

BOT-05 does not resolve canonical conflicts. If the authoritative state layer
cannot establish canonical lineage, evidence cannot become authoritative merely
because its signature is valid or its sequence is high.

## 12. Preservation Contract

Non-authoritative verification does not mean deletion. Evidence artifacts are
inputs to verification; BOT-05 has no deletion API.

## 13. Cryptographic Safety Contract

The repository implementation must not claim that the included test doubles
provide cryptographic security. Production integration must inject a real
cryptographic verifier and a real canonical state implementation.

## 14. Testing Requirements

Tests must cover at minimum:

- valid canonical evidence;
- invalid signature;
- signer ineligible at issuance;
- historical evidence after signer revocation;
- non-canonical lineage;
- same-position conflicting roots delegated to state authority;
- wrong domain/subject/resource/context;
- purpose mismatch;
- insufficient coverage;
- stale/superseded current-authority claim;
- missing freshness certification;
- reusable evidence not consumed;
- single-use first consumption;
- single-use replay;
- missing consumption boundary;
- complete canonical verification integration flow.

## 15. Completion Gate

BOT-05 is complete only when:

- Blueprint and Contract are present;
- implementation matches the approved boundaries;
- unit tests pass;
- integration tests pass;
- no cryptographic authority is invented inside BOT-05;
- no canonical state mutation exists inside BOT-05;
- completion record is present;
- implementation structure is documented;
- `git diff --check` passes;
- changes are committed and pushed to the authoritative repository.
