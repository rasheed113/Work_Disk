# BOT-50 — Tool Registry / Dispatcher
Final reusable dispatch boundary for Work_Disk Tool Bots. Provider owns registration, version selection, capability checks, lifecycle, routing and persistence. Attacks: tool spoofing, authority escalation, capability confusion, version substitution, stale registry, cross-account leakage, replay, duplicate dispatch, disabled-tool invocation, provider failure, routing ambiguity, hidden side effects, UI coupling, persistence leakage, policy bypass, untrusted tool metadata, boundary drift.

## Contract
BOT-50 validates request, authority, actor, tool and operation references, then delegates dispatch. It does not grant authority, implement individual tool behaviour, or hardcode tool availability.
