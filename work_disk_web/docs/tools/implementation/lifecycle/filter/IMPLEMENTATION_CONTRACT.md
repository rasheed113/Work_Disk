# BOT-10 — Filter Tool Bot: Implementation Contract

## Identity
BOT-10 is the Filter Tool Bot. It is a reusable lifecycle/tool boundary and is not a page-specific feature.

## Inputs
A request MUST contain:

- request_id
- authority_reference
- scope_reference
- target_type
- at least one criterion
- limit greater than zero

Each criterion MUST contain a non-empty field.

## Authority invariant
Authority MUST be checked before the FilterProvider is invoked. A rejected request MUST NOT reach the provider.

## Scope invariant
The provider MUST interpret `scope_reference` as the complete authorised search/filter boundary. BOT-10 never expands it.

## Mutation invariant
BOT-10 MUST NOT mutate source records or selection state.

## Result invariant
Filtering returns a derived result. A result MUST NOT be treated as a permission grant or durable authority token.

## Ordering invariant
BOT-10 does not define ordering semantics. Sort is a separate concern.

## Provider boundary
The provider owns domain-specific field access, type semantics, data visibility within the supplied scope, pagination implementation, and storage/index details.

## Failure semantics
Invalid request → `InvalidRequest`.
Authority rejection → `AuthorityRejected`.
Provider empty result → `Empty`.
Provider execution failure → `ExecutionFailed`.

## Traceability
The contract preserves the established Tool-Bot separation used by the lifecycle tools: the tool validates its boundary, delegates domain-specific work, and does not absorb another tool's authority.
