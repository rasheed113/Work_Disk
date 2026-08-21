# BOT-34 — Search Index Tool

## Boundary
BOT-34 is a reusable search-intent boundary for multiple Work_Disk surfaces. It validates caller authority, actor, scope and query text, then delegates search execution to a provider.

## Supported intent
- Exact matching
- Prefix matching
- Token matching

## Attack register
1. Missing authority
2. Actor spoofing
3. Scope escape
4. Cross-account result leakage
5. Query injection into provider policy
6. Result substitution
7. Hidden ranking authority
8. Index staleness
9. Replay
10. Duplicate requests
11. Provider failure
12. Timing side-channel exposure
13. Deleted-data resurfacing
14. Permission drift
15. UI coupling
16. Search-policy leakage
17. Boundary drift

## Non-responsibilities
BOT-34 does not grant permissions, own indexes, decide ranking policy, expose deleted records, or mutate domain data.

## Contract
Required request, authority, actor, scope and query references are validated before provider delegation. Provider owns indexing, filtering, ranking, freshness and persistence policy.

## Testing rule
Contract tests use deterministic input fixtures only to exercise validation/delegation behaviour; they do not pretend to be a production search backend or hardcode production results.
