# BOT-31 — Case Workflow Tool

## Boundary
BOT-31 provides a reusable authorised case-workflow mutation boundary for opening, updating and closing a case. Provider owns persistence, lifecycle policy, concurrency and evidence retention.

## Attack register
1. Missing authority
2. Actor spoofing
3. Case substitution
4. Cross-account leakage
5. Invalid transition
6. Replayed mutation
7. Duplicate request
8. Stale state
9. Scope escalation
10. Evidence substitution
11. Provider failure
12. Partial persistence
13. Close-without-case
14. Update-without-payload
15. UI coupling
16. Domain-policy leakage
17. Boundary drift

## Contract
Required request/authority/actor references are validated before provider delegation. Open requires payload; update and close require an existing case reference. The tool does not decide external policy or own storage.
