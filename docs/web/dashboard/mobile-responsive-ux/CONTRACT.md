# Work_Disk Web — Dashboard Mobile Responsive UX Contract

## Sealed rules

- Customize Mode is presentation-only ephemeral UI state.
- Normal mode does not permanently expose Pin, Move or Hide controls on runtime cards.
- Customize Mode may expose existing Pin, Move and Hide/Unhide operations.
- Hide/Unhide is always non-destructive; Delete is not introduced.
- View Mode remains exactly `grid | list`.
- Grid Columns remains exactly `2 | 3 | 4`.
- Default presentation remains `grid + 2`.
- Mobile Grid remains a real two-column Grid under the existing View Mode v2.1 responsive policy.
- Mobile List remains one column.
- Responsive CSS must prevent horizontal overflow from card or nested content.
- Empty states must remain truthful to the authoritative Dashboard model and must not fabricate records.
- Customize Mode must not access domain services, repositories or persistence directly.
- Changing presentation mode, column preference or Customize Mode must not alter card order, hidden state, pinned state or domain data.
