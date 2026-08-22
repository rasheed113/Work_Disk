# Account Endpoint Contract

## Status
CONTRACT LOCKED / REUSABLE ENDPOINT BOUNDARY IMPLEMENTED

The shared Web HTTP runtime transport provider and the reusable Account runtime endpoint boundary are implemented. Final HTTP-server mounting remains an infrastructure concern and must use this boundary rather than duplicate its rules.

## Operation
`account.get`

## Authority
BOT-01 `AccountService::getAccount(accountId)` is the authoritative source. The endpoint boundary owns transport adaptation only; it does not create, mutate, authenticate, or invent Account data.

## Request
```json
{
  "operation": "account.get",
  "requestId": "<caller-generated-id>",
  "payload": {
    "accountId": "<account-id>"
  }
}
```

## Response
```json
{
  "requestId": "<same-id>",
  "state": "AUTHORITATIVE | EMPTY | ERROR",
  "payload": "<authoritative Account serialization> | null",
  "error": "<structured error> | null"
}
```

## Rules
- `requestId` must round-trip unchanged.
- `AUTHORITATIVE` requires a non-null authoritative Account payload.
- `EMPTY` represents truthful absence and has a null payload.
- `ERROR` has a null payload and a structured error.
- The endpoint boundary delegates through `AccountAuthoritativeReadService`; production wiring must bind that interface to BOT-01 `AccountService::getAccount(accountId)`.
- It must not manufacture Account fields, IDs, credentials, lifecycle state, or authentication results.
- It must not bypass BOT-01 repositories or replace Account authority with presentation state.
- Authentication/session authority remains outside this read endpoint.
- Serialization is transport representation only; it is not a second Account domain model.

## HTTP Mapping
- `POST /api/v1/account/get`
- `Content-Type: application/json`
- HTTP status mapping must not alter envelope semantics.

## Reusable Implementation
`AccountWebRuntimeEndpoint` is the reusable endpoint boundary. It provides operation validation, Account ID validation, authoritative delegation, truthful `EMPTY` handling, explicit `ERROR` handling, correlation preservation, and no fabricated payloads.

A concrete HTTP server/router can mount this handler without changing the Account BOT contract.

## Integration Boundary
HTTP provider BOT → `AccountWebRuntimeEndpoint` → BOT-01 `AccountService::getAccount(accountId)` → authoritative Account read model → serialized response → `AccountPresentationAdapter` → Settings Account Page Property.

## Verification
The reusable endpoint boundary is covered by tests for authoritative delegation, truthful empty state, missing Account ID rejection, unregistered operation rejection without domain invocation, and authoritative read failure without fabricated data.

## Infrastructure Gate
The repository currently does not expose a concrete HTTP server/router implementation. Therefore no server framework or route registration has been invented. When the runtime server is introduced, its only responsibility here is to decode the HTTP request, invoke `AccountWebRuntimeEndpoint.handle(...)`, and encode the returned envelope.
