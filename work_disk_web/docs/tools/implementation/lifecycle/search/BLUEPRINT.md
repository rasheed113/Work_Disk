# BOT-08 — Search 🔎 Blueprint

## Purpose
BOT-08 is a generic, multi-caller, domain-neutral read-only Tool Bot for authorised retrieval from a caller/domain supplied searchable scope.

## Boundary
Caller/domain/authority owns:
- account, role, relationship, and permission policy
- searchable scope construction
- target lifecycle visibility
- field-level projection/redaction
- domain validation and business semantics
- index freshness and consistency guarantees

BOT-08 owns:
- generic request validation
- invoking the supplied authority boundary
- forwarding search criteria without domain reinterpretation
- invoking the search provider only after authority succeeds
- explicit result-code reporting

## Search modes
The generic contract supports Exact, Keyword, Prefix, Identifier, and Filter modes. Domain-specific matching semantics remain provider-owned.

## Result model
Results contain opaque target type/id references and provider-supplied ranking/cursor data. BOT-08 does not return arbitrary domain records or sensitive fields by itself.

## Non-goals
BOT-08 does not edit, delete, archive, trash, mark, notify, grant permission, decide ownership, or define domain lifecycle policy.

## Multi-page use
Any authorised page/domain may call the same bot with its own scope, target type, criteria, and provider. Separate page implementations must not bypass the authority boundary.

## Failure semantics
Invalid requests, authority rejection, invalid scope, empty results, and provider execution failure remain distinguishable.
