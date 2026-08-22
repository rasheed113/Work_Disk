# Work_Disk Web — Navigation Buttons Bot Contract

## Sealed rules

1. Navigation is a dedicated presentation boundary, not Dashboard content.
2. The Navigation Buttons Bot is the single authoritative owner of workspace navigation presentation.
3. The initial navigation registry contains exactly Dashboard, Finance, History, Settings and Profile.
4. Dashboard navigation is visible on the Dashboard surface.
5. Dashboard navigation is hidden on the Social/Feed surface.
6. Navigation visibility must be surface-aware and presentation-only.
7. Navigation items are never registered as Dashboard cards.
8. Navigation items are never affected by Dashboard Grid/List, Grid Columns, Hide/Unhide, Pin/Unpin or Reorder operations.
9. The bot must not access domain repositories/services directly.
10. The bot must not create or infer Account, Profile, permission or Tool-Bot authority.
11. Search, Filter and Sort are not part of this bot unless a separate explicit contract authorises them.
12. Mobile bottom navigation is viewport presentation; it must not become scrollable Dashboard content.
13. Desktop navigation presentation must remain independent from Dashboard card presentation.
14. Unknown navigation destinations are rejected/ignored by the presentation adapter rather than silently invented.
15. Any future navigation destination requires a contract update and corresponding tests before implementation.
