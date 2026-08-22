# Work_Disk — Transport Infrastructure Contract

## Status
DESIGNED / CONTRACT LOCKED

## Decision
The first concrete C++ runtime transport is a minimal HTTP/JSON boundary implemented behind Work_Disk's existing Web Transport Provider contract.

No domain logic, identity authority, or persistence is moved into the transport layer.

## Infrastructure Boundary
HTTP listener/runtime
→ route dispatcher
→ endpoint handler
→ authoritative BOT/service
→ endpoint response envelope

## JSON Boundary
JSON parsing/encoding is isolated behind a transport codec interface. Domain models are never serialized by ad-hoc string concatenation.

## Required Runtime Guarantees
- POST-only for mutation/read operation envelopes defined by endpoint contracts.
- `requestId` correlation preserved end-to-end.
- malformed JSON/request rejected explicitly.
- unknown operation rejected explicitly.
- endpoint errors never become empty/success responses.
- no generated/default domain fields.
- session/authentication remains an external authority.

## Dependency Rule
A concrete HTTP/JSON implementation may use a repository-approved dependency, but the dependency must remain behind this boundary. Dependency selection must be recorded in the build configuration and tested.

## Current Profile Target
`POST /api/v1/profile/assemble`
→ ProfileEndpointHandler
→ BOT-02 ProfileService::assemble()

## Completion Gate
Transport infrastructure is not considered runtime-complete until the build compiles it, endpoint integration tests exercise a real HTTP request/response, and the Web provider receives the authoritative envelope.
