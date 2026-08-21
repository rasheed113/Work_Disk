# BOT-19 — Comment/Reply Tool

Reusable authority-gated comment submission boundary. The tool validates request identity and delegates persistence to a provider. It does not decide permissions, render threads, mutate unrelated records, or perform moderation.

Attack focus: actor spoofing, target omission, empty body, cross-context access, stale version, replay/idempotency, provider failure, thread escalation, UI coupling, moderation bypass, and boundary drift.
