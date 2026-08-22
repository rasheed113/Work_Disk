# Work_Disk — Real-Time Web Transport Provider BOT Contract

## Status
CONTRACT LOCKED / RUNTIME PROVIDER IMPLEMENTED

## Purpose
Define the single shared transport-provider boundary between the Work_Disk authoritative C++ service/BOT layer and the Web presentation runtime.

## Architectural Decision
The provider boundary is shared across pages and BOTs. Page-specific presentation adapters remain downstream and are never replaced by this transport BOT.

## Authoritative Flow
Authoritative BOT/Service
→ Web Transport Provider BOT
→ Web runtime transport response
→ Page-specific Presentation Adapter
→ Page View Model
→ UI

## Protocol Decision
The first concrete runtime provider uses **HTTP request/response over the Web runtime's standard fetch transport**.

Rationale:
- deterministic request/response semantics fit authoritative read operations;
- browser-native and provider-neutral;
- simple authentication/session propagation boundary;
- compatible with incremental BOT-by-BOT rollout;
- avoids introducing persistent connection semantics before a real-time event contract is required.

A persistent WebSocket provider is NOT part of this first contract. It may be introduced later only through a separate authoritative event/stream contract.

## Provider Responsibilities
- establish the Web-to-runtime HTTP transport boundary;
- carry an explicit operation identifier;
- carry an authoritative request payload;
- propagate authenticated session/context metadata without becoming its authority;
- return authoritative, empty, or explicit transport failure state;
- preserve request/response correlation;
- reject malformed/unrecognised operations;
- never fabricate domain data.

## Provider Non-Responsibilities
- domain business logic;
- profile/search/notification ownership;
- presentation transformation;
- domain persistence;
- permission decisions;
- inventing BOT contracts;
- fake/default payload generation.

## Wire Envelope
Request:
- `operation`: stable BOT/service operation identifier;
- `requestId`: caller-generated correlation identifier;
- `payload`: contract-defined operation payload;
- `context`: transport-safe session/context metadata.

Response:
- `requestId`: correlation identifier;
- `state`: `AUTHORITATIVE | EMPTY | ERROR`;
- `payload`: authoritative operation result or null;
- `error`: structured transport/application error or null.

## Empty Semantics
`EMPTY` is a truthful authoritative result. It is not an error and must not be converted to placeholder data.

## Error Semantics
Transport/provider failure is explicit. The provider must not convert an error into `EMPTY` or fabricate a payload.

## Security Boundary
The provider transports authenticated context but does not create, verify, revoke, or redefine identity/session authority. Those remain owned by the authoritative identity/session contracts.

## Runtime Implementation
The first concrete runtime provider is implemented as:

`FetchHttpTransportClient`
→ browser `fetch`
→ `HttpWebTransportProvider`
→ shared presentation transport boundary.

Implementation rules:
- endpoint resolution is supplied explicitly by the caller;
- an unrecognised operation is rejected rather than converted into a guessed URL;
- `requestId` is sourced from the caller correlation ID and must round-trip unchanged;
- `AUTHORITATIVE` requires a non-null payload;
- `EMPTY` requires a null payload;
- `ERROR` requires a null payload;
- malformed envelopes are rejected;
- network/HTTP/response failures remain explicit transport failures;
- authenticated context is transported but never interpreted as domain authority.

The runtime provider is domain-neutral. The Account endpoint remains a separate endpoint-handler concern governed by `ACCOUNT_ENDPOINT_CONTRACT.md` and must delegate to BOT-01 `AccountService::getAccount(accountId)`.

## Profile Vertical Slice
BOT-02 `ProfileService::assemble(...)`
→ provider operation `profile.assemble`
→ authoritative profile assembly snapshot
→ `ProfilePresentationAdapter`
→ Dashboard Profile UI.

The provider does not assemble profile data itself.

## Verification
The runtime provider is covered by tests for:
- authoritative response preservation;
- empty response preservation;
- correlation preservation and mismatch rejection;
- malformed authoritative payload rejection;
- unrecognised operation rejection;
- browser HTTP request mapping;
- transport response validation.

## Evolution Rule
Any new protocol, streaming mode, or wire-envelope change requires a new contract revision and corresponding tests. No silent protocol invention is permitted.
