# BOT-33 Attack Register — Audit Trail Tool

1. Missing authority
2. Actor spoofing
3. Subject substitution
4. Event identity collision
5. Evidence substitution
6. Cross-account leakage
7. Cross-role context confusion
8. Timestamp manipulation
9. Sequence rollback
10. Replay / duplicate append
11. Provider failure
12. Partial persistence
13. Silent mutation of history
14. Privilege escalation through audit records
15. UI-coupled provenance
16. Disclosure of sensitive evidence
17. Boundary drift

Verdict: BOT-33 is an append-intent boundary. The provider remains authoritative for durable storage, uniqueness, ordering, retention, redaction policy and conflict handling.