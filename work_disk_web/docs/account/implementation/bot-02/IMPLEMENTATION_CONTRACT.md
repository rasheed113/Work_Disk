# Work_Disk Web — Account — BOT-02
# Implementation Contract

## 1. Purpose

This contract converts the approved BOT-02 Profile Assembly Point architecture into the minimum concrete requirements required for implementation.

This document does not create new architecture.

## 2. Fresh Project Boundary

Implementation must use only:

- Current Work_Disk Web architecture
- BOT-02 approved Blueprint
- This implementation contract

The following are not implementation sources:

- Previous Work_Disk code
- Previous Work_Disk database designs
- Previous Bot implementations
- Historical security architecture
- Historical validation architecture
- Historical profile implementations
- Historical implementation assumptions

## 3. Implementation Structure

BOT-02 implementation belongs under:

src/account/bot-02/

Expected responsibility directories may include:

- models/
- repositories/
- services/
- utils/
- validators/

Tests belong under:

tests/account/bot-02/

with:

- unit/
- integration/

Create only files required by the approved implementation scope.

## 4. Model Boundary

The Profile model may contain only profile information explicitly required by the BOT-02 architecture.

The implementation must not invent:

- New profile states
- New identity types
- New ownership rules
- New relationships
- New security architecture
- New deletion rules

## 5. Repository Boundary

Repositories own persistence interaction required by BOT-02.

Repositories must not:

- Perform authorization decisions
- Generate IDs
- Implement generic editing
- Implement permanent deletion engines
- Implement feed ranking
- Implement intelligence

## 6. Service Boundary

Services own Profile business operations explicitly required by BOT-02.

Business rules must remain within the appropriate Profile service/domain boundary.

Services must not silently absorb future tool responsibilities.

## 7. Validator Boundary

Validators may enforce profile requirements explicitly defined by the architecture.

Validators must not create independent authentication, authorization, privacy, or security architectures.

## 8. Completion Contract

The implementation must represent:

- Completion percentage
- Completion state
- Missing requirements
- Completion suggestions

Completion must remain deterministic for the authoritative profile state.

Shared Intelligence may provide advisory information but cannot silently mutate the profile.

## 9. Media Contract

BOT-02 stores or manages authorised references to:

- Current Profile Picture
- Current Cover Picture
- Historical profile media

Replacement must preserve the previous media as historical content.

Explicit permanent deletion must remain outside BOT-02's deletion engine.

## 10. History Contract

Profile history must be capable of representing authorised historical shared content and its relevant timestamp/privacy reference.

BOT-02 must not duplicate the authoritative Social/Post content itself unless explicitly required by architecture.

## 11. Privacy Contract

BOT-02 must respect the authorised privacy decision before exposing protected profile information.

The implementation must support the architectural visibility concepts:

- Only Me
- Friends & Followers
- Global

BOT-02 must not bypass the Privacy system.

## 12. ID Contract

BOT-02 consumes generated identifiers.

It must never generate Account IDs, Profile IDs, Fleet IDs, Entry IDs, or other future identifier classes.

## 13. External Tool Contract

Camera, Gallery, Edit, Delete, Search, Notification, ID Generation, Social/Post processing, and Intelligence are external boundaries.

BOT-02 may request or consume their defined outputs but must not implement those systems internally.

## 14. Tests

BOT-02 must test every implemented behaviour.

Tests must cover, where applicable:

- Valid profile creation/state
- Invalid profile input
- Completion boundaries
- Missing profile requirements
- Media replacement
- Historical media preservation
- History timestamps
- Privacy visibility boundaries
- Independent account/profile ownership
- Failure behaviour
- Repository/service interaction

Tests must verify current architecture, not historical Work_Disk behaviour.

## 15. Integration Testing

At least one integration flow must verify the complete approved BOT-02 assembly path.

The integration test must verify that profile assembly does not destroy or overwrite unrelated account data.

## 16. Decision Stop Rule

If implementation encounters an undefined architectural decision:

STOP.

Do not guess.

Do not copy old code.

Do not create an implementation-specific architectural rule.

Record the missing decision and return to architecture.

## 17. Completion Gate

BOT-02 can be marked complete only when:

- Approved implementation is complete
- Required unit tests pass
- Required integration tests pass
- Boundaries are respected
- No legacy architecture has been imported
- No unrelated tools have been embedded
- No unresolved architectural decision has been hidden inside code
- Completion record has been created
- Git working tree is clean
- Changes are pushed to the authoritative repository
