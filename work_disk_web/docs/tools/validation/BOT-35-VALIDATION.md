# BOT-35 — Validation Tool

## Boundary
BOT-35 is a reusable validation-intent boundary. It validates that an authorised caller supplies the required references, then delegates the actual rule evaluation to a provider.

## Operations
- Validate
- Revalidate

## Attack register
1. Missing authority
2. Actor spoofing
3. Subject substitution
4. Rule substitution
5. Value substitution
6. Cross-account leakage
7. Scope escalation
8. Replay
9. Duplicate validation
10. Stale rule reference
11. Provider failure
12. Validation-result forgery
13. Hidden mutation
14. Permission drift
15. UI coupling
16. Policy leakage
17. Boundary drift

## Non-responsibilities
BOT-35 does not define business rules, grant permissions, mutate domain records, own policy storage, authenticate credentials, or fabricate validation outcomes.

## Contract
Required request, authority, actor, subject, rule and value references are checked before provider delegation. The provider owns rule evaluation and persistence semantics.

## Testing integrity
Tests use deterministic local fixtures only for validation/delegation behaviour. They do not emulate a production rules engine or hardcode production validation outcomes.
