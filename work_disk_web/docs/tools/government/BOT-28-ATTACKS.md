# BOT-28 Attack Register

1. Missing authority
2. Actor spoofing
3. Missing service reference
4. Missing payload
5. Replay / duplicate submission
6. Cross-account leakage
7. Cross-context confusion
8. Forged case reference
9. Provider failure
10. Stale state
11. Permission escalation
12. Workflow bypass
13. UI coupling
14. Oversized input
15. Malformed references
16. Inconsistent operation semantics
17. Boundary drift

Verdict: no architecture-level blocker at the Tool boundary. Provider owns persistence, deduplication and workflow semantics.