# BOT-05 — Warning & Approval Bot — Profile

| Field | Value |
|---|---|
| Bot Number | BOT-05 |
| Real Name | Warning & Approval Bot |
| Category | Tool Bot |
| Caller Model | Multiple authorised callers |
| Primary Capability | Create warning/approval gate and route terminal decision |
| Terminal Decisions | Approved / Rejected |
| Pending State | Yes |
| Automatic Expiry | No |
| Executes Protected Action | No |
| Owns Notification Transport | No |
| Owns Permission/Approver Authority | No |
| Domain-Specific | No |
| Source Location | `src/tools/bot-05-warning-approval/` |
| Test Location | `tests/tools/bot-05-warning-approval/` |

## Boundary Statement

> Warning & Approval Bot creates the gate and carries the decision signal; the owning action bot remains responsible for the actual action.

## Required Integration Rule

Any bot integrating BOT-05 must provide a uniquely identifiable request context and must consume the returned decision through its own action boundary.
