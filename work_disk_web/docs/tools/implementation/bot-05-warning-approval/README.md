# BOT-05 — Warning & Approval Bot

BOT-05 is a reusable Work_Disk tool bot for actions that require an explicit human or external authority decision before completion.

## Boundary

BOT-05 creates the warning/approval gate, calls the notification boundary, receives the terminal decision, and routes that decision back to the registered action consumer.

It does not execute the protected action.

## Multi-Caller

BOT-05 is intentionally generic. Multiple authorised bots may create independent approval requests at the same time. Each request is isolated by `approvalRequestId`.

Examples include Fleet, Social, Account, finance, or future domain/tool workflows where explicit approval is required.

## Decision Model

- `Pending` — warning exists and approval is still required.
- `Approved` — positive terminal signal.
- `Rejected` — negative terminal signal.

There is no automatic expiry. Silence never becomes approval or rejection.

## Notification Separation

Notification delivery is a transport concern. A sent/read notification is never itself an approval.

## Action Separation

The action owner consumes the final decision. BOT-05 does not call Delete Bot, Freeze Bot, or any domain mutation executor.

## Location

- Documentation: `docs/tools/implementation/bot-05-warning-approval/`
- Source: `src/tools/bot-05-warning-approval/`
- Tests: `tests/tools/bot-05-warning-approval/`
