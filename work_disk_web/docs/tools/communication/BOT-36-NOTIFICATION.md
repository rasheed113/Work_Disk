# BOT-36 — Notification Tool

Reusable authorised notification intent boundary. Provider owns delivery channels, persistence, retries, ordering, deduplication and user preferences.

## Attacks
1. Authority spoofing
2. Recipient substitution
3. Cross-account leakage
4. Replay
5. Duplicate delivery
6. Channel escalation
7. Preference bypass
8. Payload tampering
9. Provider failure
10. Retry storm
11. Ordering confusion
12. Stale recipient state
13. Hidden side effects
14. UI coupling
15. Privacy leakage
16. Delivery-policy leakage
17. Boundary drift

## Contract
Required request, authority, actor and recipient references are validated before provider delegation. BOT-36 does not deliver messages, own notification storage, bypass preferences or grant authority.
