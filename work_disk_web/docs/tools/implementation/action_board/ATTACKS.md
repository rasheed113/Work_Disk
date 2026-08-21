# Action Board — Attack Register

## Scope

Action Board is a discovery/routing boundary. It never executes the selected action.

## Attack set

1. Missing authority — reject before provider access.
2. Missing context — reject.
3. Missing selection — reject.
4. Empty selection — reject unless `all_in_scope` is true.
5. Cross-account leakage — authority boundary must reject.
6. Cross-role leakage — authority boundary must reject.
7. Selection-as-permission — selection is not permission.
8. Action-as-execution — discovery must not execute tools.
9. Hard-coded actions — provider owns applicable action discovery.
10. UI coupling — board returns descriptors, not UI widgets.
11. Domain coupling — context is opaque.
12. Provider failure — propagate failure without mutation.
13. Stale selection — downstream action must revalidate state.
14. Deleted targets — downstream action owns target validity.
15. Mixed-capability selection — provider may expose partial/conditional actions.
16. Mark-All scope escape — selection reference remains bounded by supplied scope.
17. Replay — request identity remains caller-controlled; execution is downstream.
18. Sensitive action metadata — descriptors contain only safe identifiers/labels.
19. Action impersonation — tool reference is declarative, not executable.
20. Boundary drift — no Delete/Move/Archive logic belongs here.

## Verdict

No unresolved architecture-level blocker. The Action Board is a capability discovery boundary, not a generic execution bot.
