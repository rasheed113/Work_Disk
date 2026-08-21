# Account/Profile + Workspace — Blueprint

## Presentation package

`src/presentation/features/account-profile-workspace/`

- `model.ts` — domain-neutral presentation contracts
- `AccountProfileSurface.tsx` — account/profile composition
- `WorkspaceShell.tsx` — application workspace framing
- `workspace.css` — feature-local visual treatment using shared design language

## Contract inputs

`AccountProfileModel | null`

The model is read-only presentation data. A future adapter may map authoritative Account/BOT-02 profile state into it without changing the UI contract.

## Visual blueprint

- Bright professional base
- Shared 3D surface primitives and design tokens
- Medium/professional card sizing
- Controlled motion only
- Responsive workspace grid
- Clear empty states
- No fabricated production identity data

## Integration

The application router exposes `/workspace` and `/profile`. The Workspace Shell links to Dashboard, Profile and Settings. Settings remains a deferred feature surface and is not implemented by this slice.
