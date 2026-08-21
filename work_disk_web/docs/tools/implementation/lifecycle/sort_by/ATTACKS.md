# BOT-11 — Sort By Attack Register

## Attack set

01 Authority omission — reject without authority.
02 Scope omission — reject without scope.
03 Cross-account leakage — authority/scope are mandatory.
04 Cross-role leakage — caller context remains external authority.
05 Sort-as-authority — sorting never grants access.
06 Mutation leakage — sorting never changes source records.
07 Search coupling — sorting is not search.
08 Filter coupling — sorting is not filtering.
09 Mark coupling — sorting never changes BOT-09 selection state.
10 Unsupported field — domain/provider owns supported-field policy.
11 Invalid direction — typed direction only.
12 Numeric ordering — provider must apply numeric semantics for Number.
13 Size ordering — provider must use declared size semantics, not lexical text.
14 Lexical ordering — Name ordering is deterministic and provider-defined for collation.
15 Ascending/descending inversion — direction is explicit.
16 Missing values — provider must define deterministic placement.
17 Duplicate values — stable tie handling belongs to provider contract.
18 Pagination — limit is bounded and remains a view concern.
19 Empty result — valid result may contain zero targets.
20 Stale result — downstream consumers must not treat order as authority.
21 Cross-page reuse — no page policy is hardcoded.
22 Replay — request identity remains caller-owned.
23 Provider failure — provider owns retrieval failure semantics.
24 Sensitive fields — sort does not expose domain payload.
25 Unbounded work — limit and provider controls bound execution.
26 Boundary drift — no action/mutation responsibility is introduced.

## Verdict
No architecture-level blocker remains for the generic Sort By boundary.
