# Profile Endpoint Contract

## Status
DESIGNED / CONTRACT LOCKED

## Operation
`profile.assemble`

## Authority
BOT-02 `ProfileService::assemble(profileId, privacyDecision)` is the authoritative source. The endpoint handler owns transport adaptation only; it does not assemble or invent profile data.

## Request
```json
{
  "operation": "profile.assemble",
  "requestId": "<caller-generated-id>",
  "payload": {
    "profileId": "<profile-id>",
    "privacyDecision": "<contract-defined-decision>"
  }
}
```

## Response
```json
{
  "requestId": "<same-id>",
  "state": "AUTHORITATIVE | EMPTY | ERROR",
  "payload": "<authoritative ProfileAssembly serialization> | null",
  "error": "<structured error> | null"
}
```

## Rules
- `requestId` must round-trip unchanged.
- `AUTHORITATIVE` requires a non-null authoritative assembly payload.
- `EMPTY` is truthful absence and has a null payload.
- `ERROR` has null payload and a structured error.
- The handler must not manufacture profile fields, IDs, status, media, or completion values.
- The handler must not bypass `ProfileService` or its repositories.
- Authentication/session authority remains outside this endpoint handler.
- Serialization is transport representation only; it is not a second domain model.

## HTTP Mapping
- `POST /api/v1/profile/assemble`
- `Content-Type: application/json`
- Transport/application failures are represented by the envelope; HTTP status mapping is provider-specific and must not alter the envelope semantics.

## Integration Boundary
HTTP provider BOT → this endpoint handler → BOT-02 `ProfileService` → authoritative assembly → serialized response.
