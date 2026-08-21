# BOT-06 Archive 📦 — Integration Contract

## Caller contract
A domain bot calls BOT-06 with a unique request, target identity/type, authoritative authority reference, durable source reference, and expected lifecycle version.

The caller remains responsible for determining whether archive/unarchive is allowed and for any user-facing warning/notification.

## Return contract
BOT-06 returns an explicit result. Callers must publish UI or notification state only after the authoritative result is known.

## Delete interaction
BOT-04 Delete remains the owner of deletion. An archive operation must not silently become delete. If a domain chooses to delete an archived item, that is a separate authorised Delete command.

## Trash interaction
BOT-05 Trash owns deleted-item retention and destruction. Archive does not enter Trash merely because it is inactive. A domain-specific transition between archive and trash must be explicit and authorised.

## Restore/unarchive
BOT-06 only returns through the opaque source reference supplied by the caller. It does not guess an original folder, feed position, chat location, notification state, or visibility policy.

## Multi-caller isolation
One caller's domain semantics must not leak into another caller's archive operation. `targetType` and opaque references preserve separation.
