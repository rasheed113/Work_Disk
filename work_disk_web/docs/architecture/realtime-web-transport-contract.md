# WEB-TRANSPORT-01 — Shared Web Transport Contract

## Contract state
DESIGNED / SEALED AS A BOUNDARY. Concrete provider contract remains blocked until the authoritative runtime protocol is established.

## Input
A transport request is an opaque, contract-owned operation envelope supplied by an authorised application/BOT integration layer. The transport does not invent operation names.

## Output
A transport result is either:
- an authoritative payload supplied by the provider;
- an explicit empty result;
- an explicit unavailable-provider/transport error.

## Invariants
1. No dummy payloads.
2. No hardcoded domain responses.
3. No domain repository access.
4. No BOT contract invention.
5. No presentation mapping.
6. Provider failure is observable; it is not converted into fake success.
7. Authentication/session authority remains owned by the established Work_Disk identity/session architecture.
8. Page-specific presentation adapters remain responsible for UI models.

## Provider gate
A concrete provider must document protocol, serialization, authentication/session authority, reconnect semantics, timeout/error semantics, and testable security invariants before runtime wiring is marked IMPLEMENTED.
