# BOT-10 — Filter Tool Bot: Attack Report

## Scope
Filter is a derived-view operation. It must narrow an authorised input scope without mutating source data or creating authority.

## Attack set

1. **Authority omission** — reject requests without authority reference.
2. **Scope omission** — reject requests without scope reference.
3. **Cross-account leakage** — provider must operate only within the supplied authorised scope.
4. **Cross-role leakage** — filter cannot broaden a role/context boundary.
5. **Search-as-authority** — filtering cannot grant access to records.
6. **Mutation leakage** — filter cannot edit, delete, archive, move, or mark records.
7. **Field injection** — field names are data, not executable query fragments.
8. **Unbounded result abuse** — zero limit is rejected; provider owns bounded pagination semantics.
9. **Empty criteria** — reject because a filter operation must have an explicit predicate.
10. **Mixed predicate ambiguity** — `All` and `Any` are explicit; no implicit boolean semantics.
11. **Sensitive-field exposure** — filter returns identifiers/results, not unrestricted raw records.
12. **Stale scope** — downstream operation must revalidate authority/state; filter output is not a permission token.
13. **Deleted records** — domain/provider policy decides visibility inside the authorised scope.
14. **Concurrent changes** — filter is a derived snapshot; later actions must revalidate.
15. **Cross-page coupling** — no page/UI implementation is hardcoded into BOT-10.
16. **Sort coupling** — Filter does not define ordering; sorting remains a separate concern.
17. **Mark coupling** — Filter does not create or alter BOT-09 selection state.
18. **Provider failure** — provider result is propagated as a result code; no fabricated success.
19. **Replay** — request identity remains caller-visible; idempotency is not invented as a mutation guarantee.
20. **Boundary drift** — new operators require contract review rather than silent semantic expansion.

## Verdict
No architecture-level blocker was identified. BOT-10 may proceed as a domain-neutral filtering boundary, subject to downstream provider contracts preserving the supplied authority and scope.
