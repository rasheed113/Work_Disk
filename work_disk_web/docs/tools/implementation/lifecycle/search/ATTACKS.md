# BOT-08 — Search 🔎 Attack Register

## Attack review

- 08A Scope omission — reject requests without an opaque searchable scope.
- 08B Authority omission — reject requests without an authority reference.
- 08C Cross-account leakage — caller/domain authority must constrain the scope before provider execution.
- 08D Cross-role leakage — role/context changes cannot silently broaden the supplied scope.
- 08E Search-as-permission — BOT-08 never manufactures or grants authority.
- 08F Search-as-mutation — BOT-08 exposes no edit/delete/archive operation.
- 08G Sensitive-field exposure — result hits are opaque target references; field projection remains domain-owned.
- 08H Domain hardcoding — no chat, profile, entry, fleet, or other domain policy is embedded.
- 08I Query omission — a request needs either a query or criteria.
- 08J Criteria semantics — field/operator/value are caller/provider data, not BOT-08 business rules.
- 08K Exact/keyword/prefix/identifier/filter modes — represented as generic search modes.
- 08L Pagination abuse — a non-zero limit is required; the provider owns cursor semantics.
- 08M Result ranking — ranking is provider output, not an authority decision.
- 08N Empty result ambiguity — `Empty` is explicit and is not treated as failure.
- 08O Provider failure — execution failure is explicit and does not become a fabricated result.
- 08P Provider authority bypass — provider is invoked only after BOT-08 authority succeeds.
- 08Q Stale/deleted records — visibility remains caller/domain/provider policy; BOT-08 does not invent lifecycle semantics.
- 08R Concurrent changes — read consistency/snapshot semantics belong to the provider/domain contract.
- 08S Offline/index staleness — BOT-08 does not claim freshness it cannot enforce.
- 08T Cross-page reuse — the same generic boundary can serve multiple authorised callers.
- 08U Result projection — BOT-08 returns target references rather than arbitrary domain payloads.
- 08V Request replay — search is read-only; repeat execution cannot mutate state.
- 08W Invalid mode/criteria — invalid structural requests are rejected before provider execution where detectable.
- 08X Unbounded retrieval — caller must provide a finite result limit.
- 08Y Authority/result confusion — an empty result is not an authority rejection.
- 08Z Boundary drift — new search behaviour must remain inside the generic command/authority/provider separation.

## Verdict
All identified attack vectors are converted into explicit boundary or provider responsibilities. No unresolved architecture-level blocker remains for the generic Search Tool Bot implementation.
