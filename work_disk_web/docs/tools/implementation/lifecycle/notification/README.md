# BOT-16 — Notification Tool

Reusable authority-gated notification delivery boundary. Supports channel intent (in-app, push, email, SMS) while leaving transport, templates, preferences, retries and provider persistence outside the tool boundary.

## Boundary
- validates request identity, recipient, event, scope, idempotency and expected version
- checks caller authority before provider delivery
- delegates delivery to provider
- does not grant authority, mutate domain records, choose policy, or perform transport itself

## Attacks
Attack register covers authority/scope omission, cross-account and cross-role delivery, replay, duplicate delivery, stale version, invalid recipient/event, channel abuse, provider failure, payload leakage, preference bypass, transport coupling, UI coupling, notification-as-authority, and boundary drift.

## Integration
Any authorised domain may call the tool; downstream providers remain responsible for concrete delivery semantics and durable delivery state.
