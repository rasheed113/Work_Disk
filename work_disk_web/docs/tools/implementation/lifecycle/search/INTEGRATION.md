# BOT-08 — Search 🔎 Integration Contract

## Caller contract
A caller supplies:
1. request identity
2. authority reference
3. searchable-scope reference
4. target type
5. query and/or generic criteria
6. search mode
7. finite result limit
8. optional opaque cursor

## Authority contract
The caller/domain must establish the searchable scope and authority before the provider can expose matching targets. BOT-08 only invokes the supplied authority interface.

## Provider contract
The provider must honour the supplied scope and return only results permitted by its domain/search contract. Provider-owned policies include lifecycle visibility, field projection, indexing, consistency, ranking, and cursor semantics.

## Result contract
Callers receive explicit status plus opaque target references. They must not interpret a result as a permission grant or mutate the target without their own domain authority checks.

## Multi-page rule
Each page/domain may provide its own provider while reusing the same BOT-08 boundary. A page-specific shortcut that queries outside the supplied scope violates this contract.
