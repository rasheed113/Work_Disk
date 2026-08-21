# Work_Disk Web — Tools — BOT-05
# Warning & Approval Bot — Implementation Roadmap

1. **Architecture read-through** — verify BOT-05 against the existing tool-bot architecture and reusable multi-caller requirement.
2. **Boundary lock** — keep warning creation, notification invocation, decision reception, and decision routing inside BOT-05; keep action execution outside.
3. **Attack review** — execute `ATTACK_MATRIX.md` before implementation completion.
4. **Public contract** — implement request, notification, decision, state, persistence, and dispatch abstractions.
5. **Implementation** — C++17, one responsibility per file, no domain-specific action dependency.
6. **Unit tests** — validate state machine, correlation, replay, concurrency semantics, and notification separation.
7. **Integration tests** — prove a generic caller can create an approval request and receive a terminal decision without BOT-05 executing the protected action.
8. **Documentation** — complete README and PROFILE only after implementation/tests.
9. **Repository verification** — inspect diff, run formatting/checks available in repository, and verify BOT-05 tree placement.
10. **Completion** — commit implementation + documentation together after final verification; then open a draft PR for review.

## Stop Rule

If an implementation decision would make BOT-05 an action executor, permission authority, notification transport, or domain-specific workflow owner:

> STOP — return to architecture.
