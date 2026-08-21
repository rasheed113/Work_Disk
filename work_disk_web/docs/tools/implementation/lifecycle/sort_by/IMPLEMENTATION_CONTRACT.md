# BOT-11 — Implementation Contract

## Identity
BOT-11 — Sort By Tool Bot.

## Contract
1. A request must contain request ID, authority reference, scope reference, target type, and at least one criterion.
2. Authority is checked before provider execution.
3. Criteria are typed as Number, Size, or Name with explicit Ascending/Descending direction.
4. Multiple criteria are allowed for deterministic tie-breaking.
5. The provider receives the caller's scoped request and returns opaque target references.
6. BOT-11 never grants authority.
7. BOT-11 never mutates source data or BOT-09 selection state.
8. UI controls, labels, collation policy, size-unit policy, and domain field mapping remain outside BOT-11.
9. Downstream actions must perform their own fresh authority/state validation.
