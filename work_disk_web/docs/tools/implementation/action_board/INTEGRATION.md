# Action Board — Integration

## Composition

`BOT-08 Search -> BOT-10 Filter -> BOT-11 Sort By -> BOT-09 Mark/Unmark -> Action Board -> action tool`

Any stage may be omitted when a caller already has an authorised result/selection scope.

## Action display

The UI may render returned descriptors as toolbar, bottom sheet, overflow menu, or other presentation. The Action Board is UI-agnostic.

## Execution boundary

Selecting `Delete`, `Move`, `Archive`, `Download`, `Export`, or another action transfers control to that action's dedicated tool. The action tool performs fresh validation.
