# BOT-30 — Document / Records Tool

## Boundary
BOT-30 provides a reusable authorised boundary for creating, updating, archiving and restoring document/record references. Persistence, retention policy, evidence integrity, access control and domain-specific record semantics remain provider responsibilities.

## Attack register
1. Missing authority
2. Actor spoofing
3. Record substitution
4. Payload substitution
5. Cross-account leakage
6. Cross-role context confusion
7. Archive-as-delete confusion
8. Restore of unauthorised record
9. Replay/duplicate mutation
10. Stale record state
11. Retention-policy bypass
12. Evidence integrity loss
13. Provider failure
14. Scope escalation
15. UI coupling
16. Credential/identity confusion
17. Boundary drift

## Contract
Required request, authority and actor references are validated before provider delegation. Create/update require payload references; update/archive/restore require a record reference. BOT-30 does not itself decide permissions, retention, evidence validity or government/legal status.
