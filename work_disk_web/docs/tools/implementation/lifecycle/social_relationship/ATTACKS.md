# BOT-14 — Social Relationship Attack Register

1. Missing request identity.
2. Missing authority reference.
3. Missing relationship scope.
4. Missing actor.
5. Missing subject.
6. Self-relationship.
7. Invalid operation.
8. Missing idempotency key.
9. Missing expected version.
10. Relationship treated as permission.
11. Cross-account leakage.
12. Cross-role leakage.
13. Caller-chosen relationship identity.
14. Provider bypass.
15. Replay.
16. Stale version/concurrency.
17. Unauthorised accept/reject.
18. Unauthorised follow/unfollow.
19. Block/mute leakage into the core relationship tool.
20. Notification coupling.
21. Feed coupling.
22. UI/page coupling.
23. Direct source mutation outside provider authority.
24. Hidden relationship state exposure.
25. Unbounded relationship traversal.
26. Boundary drift into recommendation or moderation.

## Verdict
No architecture-level blocker identified. Concrete relationship policy and persistence remain provider/domain-owned.
