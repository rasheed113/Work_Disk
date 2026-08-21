# BOT-29 — Verification Tool

## Architecture boundary
Reusable verification-intent boundary for an authorised caller. The tool accepts a subject, authority reference and evidence reference, then delegates verification state to a provider.

## Attacks
1. Missing authority
2. Missing subject
3. Missing evidence
4. Actor spoofing
5. Evidence substitution
6. Cross-account leakage
7. Scope confusion
8. Replay
9. Duplicate verification
10. Revocation confusion
11. Provider failure
12. Stale evidence
13. Authority escalation
14. Credential confusion
15. UI coupling
16. Persistence ownership leakage
17. Boundary drift

## Non-responsibilities
BOT-29 does not mint credentials, decide platform authority, authenticate passwords, approve government cases, or own evidence storage.

## Contract
Required references are validated before provider delegation. Provider owns persistence, verification policy and conflict handling. Native CI must only be reported when a workflow run is actually observed.
