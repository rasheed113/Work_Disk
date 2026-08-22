# Account Endpoint Contract

## Status
CONTRACT LOCKED / ENDPOINT HANDLER PENDING

The shared Web HTTP runtime transport provider is implemented. The Account endpoint handler remains a separate integration gate and must not be represented as complete until it delegates to BOT-01.

## Operation
`account.get`

## Authority
BOT-01 `AccountService::getAccount(accountId)` is the authoritative source. The endpoint handler owns transport adaptation only; it does not create, mutate, authenticate, or invent Account data.

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

## Authoritative payload
The transport serialization contains only fields already exposed by the BOT-01 Account read model. The current web presentation adapter consumes `id` and `email`; no additional fields are invented at the web boundary.

## Rules
- `requestId` must round-trip unchanged.
- `AUTHORITATIVE` requires a non-null authoritative Account payload.
- `EMPTY` represents truthful absence and has a null payload.
- `ERROR` has a null payload and a structured error.
- The handler must delegate the read to BOT-01 `AccountService::getAccount(accountId)`.
- The handler must not manufacture Account fields, IDs, credentials, lifecycle state, or authentication results.
- The handler must not bypass BOT-01 repositories or replace Account authority with presentation state.
- Authentication/session authority remains outside this read endpoint.
- Serialization is transport representation only; it is not a second Account domain model.

## HTTP Mapping
- `POST /api/v1/account/get`
- `Content-Type: application/json`
- HTTP status mapping is provider-specific and must not alter the envelope semantics.

## Integration Boundary
HTTP provider BOT → this endpoint handler → BOT-01 `AccountService::getAccount(accountId)` → authoritative Account read model → serialized response → AccountPresentationAdapter → Settings Account Page Property.

## Current Gate
Completed:
- shared provider contract;
- browser Fetch runtime transport client;
- provider correlation and envelope validation;
- provider tests and transport documentation.

Pending:
- server/runtime endpoint handler for `POST /api/v1/account/get`;
- authoritative delegation to BOT-01 `AccountService::getAccount(accountId)`;
- end-to-end Account read verification through Settings.
