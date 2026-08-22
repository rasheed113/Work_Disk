# Work_Disk Web — Navigation Buttons Bot Architecture

## Purpose
Define the dedicated Navigation Buttons Bot as the authoritative presentation boundary for workspace navigation, separate from Dashboard content and Dashboard card customisation.

## Boundary

`Navigation Buttons Bot → Navigation Registry → Surface Visibility Policy → Navigation Presentation`

The bot owns navigation presentation state and surface-aware visibility. It does not own Account identity, domain data, Dashboard card data, or Dashboard card customisation.

## Navigation surfaces

The first contracted workspace navigation contains:

1. Dashboard
2. Finance
3. History
4. Settings
5. Profile

These are navigation destinations, not Dashboard cards.

## Surface visibility

- Dashboard surface: show workspace navigation.
- Social/Feed surface: do not show workspace Dashboard navigation.
- Future surfaces: visibility must be explicitly authorised by the Navigation contract.

Visibility is presentation policy only; it does not mutate domain state.

## Dashboard isolation

Navigation Buttons Bot must never enter the Dashboard card registry, card ordering, Grid/List preferences, Hide/Unhide, Pin/Unpin, Move Up/Down, or Cards Gallery content model.

## Non-goals

- No domain repository access.
- No identity authority.
- No permission authority.
- No invented Search/Filter/Sort capability.
- No destructive state changes.
