# Work_Disk Web — Dashboard Presentation Architecture Attack

## Attack target
The rendered Dashboard was audited after PR #84 visual review. The screen showed duplicated workspace navigation, configuration controls rendered as ordinary Dashboard content, and management controls competing with card content.

## Attack findings

- **Navigation duplication:** the Workspace Shell is the authoritative navigation boundary. Dashboard-local `Dashboard / Features / Settings` navigation is a duplicate presentation surface and must not render inside Dashboard.
- **Configuration-as-content:** Customize is an ephemeral presentation mode, not a Dashboard data card. A permanent `Custom Dashboard` card violates the intended mode boundary.
- **Registry-as-content:** Cards Gallery is registered-card infrastructure. It is not ordinary Dashboard content and must not render as a default Dashboard card.
- **Management density:** Hide, Unhide, Pin, Unpin and Reorder are customization operations. They belong in the explicit Customize surface, not in every runtime card header.
- **Persisted legacy state:** Previous Dashboard preferences may contain `header`, `navigation`, `customisation` or `cards-gallery` identifiers. Migration removes only those presentation-only legacy identifiers while preserving valid content order, hidden state, pinned state, view mode and grid preference.
- **Tool discovery:** BOT-08 Search, BOT-10 Filter and BOT-11 Sort By exist as generic Tool-Bot boundaries, but their documented integration candidates are domain/page callers. No Dashboard caller contract authorising these tools was found. No new Dashboard tool buttons are invented in this change.
- **Mobile density:** the existing responsive policy already constrains narrow mobile rendering to two Grid columns while preserving the stored 2/3/4 preference. That boundary remains intact.

## Surviving architecture

`Workspace Shell / Navigation → Dashboard Presentation Controls → Dashboard Content → Optional Customize Mode`

Dashboard remains presentation-only. Domain authority, Tool-Bot authority and persistence remain outside the Dashboard surface.

## Verdict
The correct fix is a presentation-boundary correction, not a rollback and not a domain change. The Dashboard is reduced to user-facing content cards; navigation, registry infrastructure and customization management are moved to their proper presentation boundaries.
