# Work_Disk Web — Footer Contract

1. Footer is a presentation boundary, not a Dashboard card.
2. Footer renders after the feature surface content in normal document flow.
3. Footer must not participate in Dashboard Grid/List, column, Customize, Hide, Pin or Reorder state.
4. Footer must not own Account, Profile, permission or domain authority.
5. Footer must not own navigation visibility; Navigation Buttons Bot remains authoritative for navigation.
6. Mobile fixed navigation must remain visually separated from Footer.
7. Footer content must be limited to explicitly registered informational items.
8. Unknown footer items are not rendered.
9. Future footer actions require an explicit contract update and tests before implementation.
