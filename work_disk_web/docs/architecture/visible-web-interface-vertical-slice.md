# Work_Disk Web — Visible Interface Vertical Slice

## Status

Implemented on `feature/visible-web-interface-vertical-slice`; merge and Main Verification remain gated on CI.

## Architecture

The visible interface is presentation infrastructure. It composes the existing Workspace Shell and Dashboard runtime; it does not become domain authority.

`Authoritative service contracts`
→ `Presentation adapters`
→ `Dashboard model`
→ `Dashboard Shell`
→ `Dashboard components`
→ `Visible Work_Disk Web`

## Attack / safety findings

- The Dashboard already has a locked twelve-component boundary.
- The Dashboard accepts a domain-neutral `DashboardModel` and does not access repositories directly.
- Customisation is non-destructive: hide/unhide, pin, reorder and reset are presentation operations; feature deletion is not a Dashboard operation.
- The visible interface must not fabricate authoritative profile identity.
- Static hosting must not become a reason to alter domain boundaries.

## Boundary

This vertical slice owns:

- entry-point routing to the visible Dashboard;
- static-host-safe client routing;
- Dashboard presentation styling;
- presentation-only contract tests;
- GitHub Pages deployment packaging.

It does not own authentication, profile persistence, permissions, domain repositories, or service authority.

## Blueprint

1. Make Dashboard the default visible Workspace destination.
2. Use hash-based client routing so static hosting does not require server-side route rewrites.
3. Use relative Vite assets so the project works beneath the repository Pages path.
4. Preserve the existing Dashboard model and component boundaries.
5. Strengthen the bright professional 3D visual surface without changing card semantics.
6. Verify the twelve-card registry and non-destructive customisation invariants.
7. Deploy the verified build through GitHub Pages.

## Contract

A successful build must expose a visible Work_Disk Dashboard at the deployed site root, preserve the twelve locked card definitions, and keep Custom Dashboard/Cards Gallery non-removable.

## Runtime rule

This is a visible presentation/runtime slice. It does **not** claim that BOT-02 is now connected to the browser through a real transport/application service. That integration remains a separate contract-gated mission.
