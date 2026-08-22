# Profile Presentation Adapter

## Status

Boundary sealed for implementation on `feature/profile-presentation-adapter`.

## Authoritative path

`BOT-02 ProfileService::assemble(profileId, privacyDecision)`
→ `ProfileAssembly`
→ transport-neutral `AuthoritativeProfileAssemblySnapshot`
→ `ProfilePresentationAdapter`
→ `DashboardProfile`
→ dashboard components.

## Boundary

The adapter is presentation infrastructure only. It:

- consumes a transport-neutral projection of the authoritative BOT-02 assembly;
- maps only fields required by the presentation model;
- returns an explicit empty result when authoritative profile data is unavailable;
- never creates profile/account identifiers;
- never writes to BOT-02 repositories;
- never becomes domain authority;
- never fabricates production profile values.

## Transport rule

`ProfilePresentationAdapter` does **not** pretend to be the runtime connection to the C++ service. A future API/WASM/application integration must produce `AuthoritativeProfileAssemblySnapshot` from the real `ProfileService::assemble(...)` result. Until that transport exists, the dashboard remains disconnected from authoritative runtime data.

## Why BOT-01/BOT-02 are unchanged

BOT-02 already exposes the authoritative `ProfileService::assemble(...)` boundary. The missing responsibility is presentation projection, so a new presentation adapter is preferred over modifying the established BOT boundary.

## Blueprint

1. Keep domain/service ownership in BOT-02.
2. Keep repository access inside BOT-02.
3. Introduce a narrow presentation DTO.
4. Map DTO → dashboard model in one adapter.
5. Test absence and anti-fabrication invariants.
6. Add the real transport implementation only after its own architecture/contract is established.
