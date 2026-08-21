# BOT-05 — Trash 🗑️

BOT-05 is the Work_Disk Trash lifecycle Tool Bot.

It keeps deleted resources recoverable for the configured retention window, supports restore, supports permanent destruction of one item, supports Empty Trash 🗑️, and supports automatic expiry purge.

## Locked product rule

**Every deleted item may remain in Trash for 3 calendar months.** During that window it can be restored. At expiry it becomes permanently destructible and automatic purge removes it when the authoritative destruction boundary succeeds.

Users may also permanently delete one Trash item or choose Empty Trash 🗑️. A successful Empty Trash operation means no current items remain in the authoritative Trash scope.

## Architecture rule

BOT-05 does not own identity, permission, approval, notification, serialization, scheduling, or domain-specific restore policy. Those concerns stay behind explicit boundaries.

## Emoji rule

User-facing UI may use real colourful Unicode emoji such as **🗑️** and **↩️**. Core code does not use emoji as control values or identifiers.

## Status

Architecture, attack register, implementation contract, roadmap, profile and reference implementation are present. Production persistence and domain integration remain explicit integration work.
