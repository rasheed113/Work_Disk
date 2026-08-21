# Action Board — Implementation Contract

## Contract

1. Action Board is a reusable, multi-caller, domain-neutral discovery component.
2. A request must contain request identity, authority reference, context, and a non-empty selection or `all_in_scope=true`.
3. Authority is checked before provider discovery.
4. Authority rejection must not call the provider.
5. Provider discovery is declarative; it must not execute an action.
6. Returned tool references are opaque routing metadata, not executable authority.
7. Action Board never mutates domain data.
8. Action Board never grants permission or ownership.
9. Every actual action tool must perform fresh authority/state validation before execution.
10. BOT-09 remains the owner of selection state.
11. Domain/page-specific action availability belongs to the ActionProvider/capability layer.
12. UI presentation is outside the component.
