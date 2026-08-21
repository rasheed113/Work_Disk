# Work_Disk Web Component System Contract

## Status

SEALED.

## Non-negotiable rules

1. Presentation components are not domain authorities.
2. Components receive data through typed contracts or adapters.
3. Direct SQLite, repository, persistence, authentication-authority, or domain-mutation access from presentation components is prohibited.
4. Relevant components must preserve explicit loading, empty, error, and success states.
5. Public component APIs must be typed.
6. Accessibility is part of the component contract.
7. Responsive behaviour must not alter domain semantics.
8. Motion must be optional/reducible and must not block core interaction.
9. 3D effects use shared visual primitives rather than duplicated component-specific systems.
10. Card sizing remains professional and information-dense; oversized blocks are not the default.
11. Generic components must not import specialised feature modules.
12. Specialised components may compose generic components.
13. Dashboard components remain governed by the existing Dashboard contract and 12 core boundaries.
14. Hide/Unhide is presentation state and never deletes a feature or domain data.
15. Cards Gallery exposes only registered and eligible components.
16. Test fixtures must never be represented as production records.
17. Component tests verify observable contract behaviour.
18. Visual tokens, motion primitives, and layout primitives are infrastructure, not additional domain components.
19. Component registry metadata describes eligibility and composition; it does not grant domain authority.
20. Any component requiring domain mutation must use an approved service/adapter boundary.

## Change control

A new reusable component requires boundary justification, contract definition, tests, documentation, and review before becoming part of the shared system.
