# Work_Disk Web — Dashboard Mobile Responsive UX Boundary

## Ownership

### Dashboard presentation boundary
Owns:
- responsive grid sizing
- mobile overflow containment
- card wrapping and intrinsic-size safety
- presentation toolbar
- Customize Mode visibility

Does not own:
- profile authority
- capabilities authority
- notifications authority
- domain persistence
- authentication or identity

### Customize Mode
Customize Mode owns only the temporary visibility of presentation-management controls.

It may expose existing operations:
- Pin/Unpin
- Move
- Hide/Unhide
- View Mode
- Grid Columns
- Reset

It does not create new domain mutations.

## Boundary invariant

A presentation correction must never require direct access to a domain repository or service.
