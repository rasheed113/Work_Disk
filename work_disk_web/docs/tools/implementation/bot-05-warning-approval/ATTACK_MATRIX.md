# BOT-05 Warning & Approval Bot — Attack Matrix

## Purpose

This matrix closes the principal authority, replay, correlation, concurrency, delivery, and recovery doubts before implementation is treated as complete.

| Attack | Failure Attempt | Required Defence | Result |
|---|---|---|---|
| A1 Request Substitution | Reuse a valid approval against another target | Bind request ID + caller + action + target + approver | Defeated |
| A2 Unknown Request Decision | Submit approval for nonexistent request | Require existing request | Defeated |
| A3 Caller Spoofing | Caller B reuses caller A's request | Caller identity is part of request authority/correlation | Defeated |
| A4 Approver Spoofing | Non-approver sends decision | Decision must authenticate/correlate approver identity | Defeated |
| A5 Notification Equals Approval | Treat delivery/read as acceptance | Notification result never changes approval state | Defeated |
| A6 Silence Equals Approval | No response is interpreted as consent | Pending remains pending; no expiry/timeout promotion | Defeated |
| A7 Silence Equals Rejection | No response silently cancels action | Pending remains pending | Defeated |
| A8 Double Decision | Approve then reject | First terminal decision is immutable | Defeated |
| A9 Replay Decision | Repeat same approval | Idempotent terminal replay | Defeated |
| A10 Cross-Request Replay | Decision for A applied to B | Exact approvalRequestId binding | Defeated |
| A11 Target Mutation | Decision payload changes target ID | Immutable request context comparison | Defeated |
| A12 Action Mutation | Approval for delete reused as transfer | Action type is immutable request context | Defeated |
| A13 Multi-Caller Collision | Concurrent callers interfere | Independent request identities and atomic state | Defeated |
| A14 Race to Decide | Two valid decisions arrive concurrently | Atomic terminal transition; one wins | Defeated |
| A15 Notification Failure | Delivery fails; bot treats it as rejection | Keep request pending | Defeated |
| A16 Dispatch Failure | Consumer cannot receive decision | Preserve committed decision; retry at dispatch boundary | Defeated |
| A17 Bot Becomes Executor | Approval bot performs protected action | No action-executor dependency/capability | Defeated |
| A18 Privilege Escalation | Approval bot invents approver authority | Authority remains external to BOT-05 | Defeated |
| A19 Request Rebinding | Same request ID reused with new target | Immutable create-if-absent semantics | Defeated |
| A20 Restart Promotion | Restart converts pending request to approved | Recover authoritative state; never manufacture approval | Defeated |
| A21 In-Memory Loss | Process restart loses pending request | Production store abstraction is authoritative | Boundary enforced |
| A22 Confused Pending State | Pending is exposed as success | Explicit Pending result | Defeated |
| A23 Cross-Domain Leakage | Fleet assumptions enter Social approval | Generic request contract; no domain dependencies | Defeated |
| A24 Duplicate Notification | Retries create duplicate action authority | Notification is non-authoritative; decision remains single-shot | Defeated |
| A25 Malformed Decision | Invalid decision shape reaches state transition | Structural validation before transition | Defeated |
| A26 Conflicting Replay | Old terminal decision competes with new terminal state | Existing terminal state dominates | Defeated |
| A27 Corrupted Context | Caller sends different warning context on decision | Compare immutable request fields | Defeated |
| A28 Hidden Expiry | Timer silently expires pending approval | No expiry primitive in BOT-05 | Defeated |

## Core Security Conclusion

BOT-05 is a **decision gate**, not an authority originator and not an action executor.

The most important invariant is:

> A valid approval decision authorises only the exact immutable request for which it was issued; it never becomes a transferable general-purpose authority token.
