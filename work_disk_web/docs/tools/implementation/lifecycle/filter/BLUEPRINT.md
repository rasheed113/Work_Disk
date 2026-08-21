# BOT-10 — Filter Tool Bot: Blueprint

## Responsibility
Provide a reusable, domain-neutral filter boundary for authorised scopes.

## Flow

Caller/Page → authority + scope + filter criteria → BOT-10 → FilterProvider → filtered identifiers/result set → caller/view layer.

## Supported predicate semantics

- Equals
- NotEquals
- Contains
- StartsWith
- GreaterThan
- GreaterThanOrEqual
- LessThan
- LessThanOrEqual

Multiple criteria use explicit `All` or `Any` matching.

## Composition

- BOT-08 Search may produce an input/result universe that a caller then filters.
- BOT-09 Mark/Unmark may consume a filtered view, but BOT-10 never changes selection state.
- Sort is intentionally outside BOT-10.
- Action bots such as Delete/Move/Archive consume their own authoritative inputs and must revalidate independently.

## UI boundary
Filter chips, sheets, checkboxes, dropdowns, and mobile/web presentation are caller concerns. BOT-10 exposes data/contract semantics only.

## Non-goals
No mutation, permission granting, ownership decisions, sorting, or raw sensitive-record projection.
