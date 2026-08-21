# BOT-05 — Warning & Approval Bot

## Identity

- Bot Number: BOT-05
- Real Name: Warning & Approval Bot
- Category: Tool Bot
- Caller Model: Multiple authorised bots

## Core Capability

Creates a warning/approval gate, invokes the notification boundary, receives an authenticated Approved/Rejected decision, and routes that decision to the registered action consumer.

## Does Not Execute

BOT-05 does not delete, freeze, unfreeze, restore, allocate, revoke, transfer, or otherwise perform the protected action.

## Approval Rule

- Pending is not approval.
- Approved is a positive terminal signal.
- Rejected is a negative terminal signal.
- No automatic expiry.
- First terminal decision wins.
- Same terminal decision is idempotent.
- Conflicting terminal decision cannot overwrite the first.

## Integration Rule

Any authorised tool/domain bot may call BOT-05. The request must bind the caller, action, target, approver, and decision consumer to one immutable approval request ID.
