# BOT-10 — Filter Integration

## Search composition
BOT-08 Search may establish an authorised result universe. A caller may pass the same authorised context to BOT-10 to narrow the view. BOT-10 does not assume Search is the only upstream source.

## Mark composition
BOT-09 may mark items shown by a filtered view. Marking remains owned by BOT-09.

## Action composition
Delete, Move, Archive, Download, Export, and future action bots must perform their own fresh authority/state validation. A filtered result is not permission.

## Sort
Sort remains separate. A caller can apply Sort after Filter without making BOT-10 responsible for ordering.

## UI
The caller owns filter controls and presentation. BOT-10 is independent of Android/Web widgets.
