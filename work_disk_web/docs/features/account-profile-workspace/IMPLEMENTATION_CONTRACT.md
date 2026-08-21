# Account/Profile + Workspace — Implementation Contract

## Invariants

1. Presentation code never owns Account or Profile domain authority.
2. Presentation code never accesses SQLite or repositories directly.
3. `AccountProfileModel` is read-only presentation state.
4. A null/missing model renders an explicit empty state.
5. No fabricated account IDs, names, credentials, roles, or capabilities are created by the UI.
6. Workspace navigation cannot grant or revoke permissions.
7. Dashboard remains a separate feature boundary.
8. Settings navigation does not imply Settings implementation.
9. Visual 3D effects must use shared presentation primitives/tokens.
10. Motion must remain controlled and non-essential to meaning.
11. Responsive layout cannot change domain semantics.
12. Feature implementation is considered complete only after tests, documentation, PR review, merge and main verification.

## Required verification

- TypeScript typecheck
- Vitest feature tests
- Production build
- Review confirms no domain persistence access or fabricated production records
