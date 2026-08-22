# Work_Disk Real-Time Web Transport

## Status
DESIGNED — shared transport boundary; concrete runtime provider is not yet authorised.

## Attack decision
Work_Disk uses one shared Web transport boundary for Web-to-authoritative-service communication. Page-specific presentation adapters remain separate. Transport does not own domain state, BOT contracts, repositories, or presentation mapping.

## Authoritative flow
`Authoritative BOT/service`
→ `Shared Web Transport`
→ `Page-specific Presentation Adapter`
→ `Page View Model`
→ `UI`

## Boundary
The transport boundary owns only:
- connection/request lifecycle;
- transport-level errors;
- request/response envelopes;
- provider capability state;
- subscription lifecycle where supported.

It does not:
- invent BOT operations;
- read domain repositories;
- mutate domain state directly;
- fabricate unavailable data;
- replace BOT contracts;
- contain page presentation logic.

## Runtime-provider gate
No HTTP, WebSocket, WASM, or other concrete provider is selected by assumption. A provider may be implemented only after an authoritative runtime protocol and its security/session rules are established from the existing Work_Disk architecture.

Until then, unavailable-provider state is explicit and must propagate to the relevant page adapter/UI as an idle/unavailable state.

## Profile vertical slice
BOT-02 remains authoritative:
`ProfileService::assemble(...)`
→ transport snapshot
→ shared transport
→ `ProfilePresentationAdapter`
→ `DashboardProfile`.

The transport must never fabricate a profile when BOT-02 data is unavailable.
