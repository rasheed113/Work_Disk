# BOT-13 — Content/Post Attack Register

## Scope
Attack the creation boundary for reusable post content without coupling it to feed, media, reactions, comments, notifications, or editing.

## Attacks
1. Missing request identity — reject.
2. Missing authority reference — reject.
3. Missing creation scope — reject.
4. Missing payload reference — reject.
5. Missing visibility policy reference — reject.
6. Missing idempotency key — reject.
7. Invalid content kind — reject.
8. Treating creation as permission — authority remains external.
9. Cross-account leakage — opaque scope prevents inference.
10. Cross-role leakage — role ownership is not inferred.
11. Payload injection — payload is referenced, not interpreted by the tool.
12. Visibility invention — policy reference is caller/domain supplied.
13. Media coupling — media acquisition is outside this tool.
14. Edit coupling — mutation after creation belongs to BOT-07.
15. Feed coupling — distribution belongs to Feed.
16. Notification coupling — delivery belongs to Notification.
17. Reaction coupling — reactions are separate.
18. Comment coupling — comments/replies are separate.
19. Replay — idempotency key is mandatory and provider-owned.
20. Provider failure — explicit ExecutionFailed result is supported.
21. UI coupling — no page, widget, or presentation is hardcoded.
22. Identifier authority — content IDs are provider/domain-owned.
23. Source mutation — tool only crosses the creation boundary.
24. Unbounded input — payload is represented by an opaque reference.
25. Sensitive projection — result returns opaque target reference only.
26. Boundary drift — all domain semantics remain outside the generic tool.

## Verdict
No architecture-level blocker identified. Concrete provider semantics remain domain-owned.
