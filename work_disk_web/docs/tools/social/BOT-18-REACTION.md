# BOT-18 — Reaction Tool

## Boundary
Reusable, authority-gated reaction application for social content. It does not create permissions, mutate unrelated data, select targets, or render UI.

## Attack coverage
Authority omission, actor spoofing, target omission, invalid reaction, duplicate/idempotency handling delegated to provider, stale version, cross-context leakage, mutation escape, provider failure, replay, UI coupling, domain coupling, and boundary drift.

## Contract
The caller supplies request id, authority, actor, target, reaction type and expected version. Provider owns persistence and concrete reaction semantics. Invalid requests are rejected before provider invocation.
