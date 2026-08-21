# BOT-13 — Content/Post Tool

Reusable content creation boundary for post-like content.

## Responsibility
Validate a creation command, require caller-supplied authority, then delegate creation to the domain-owned provider.

## Non-responsibility
No editing, feed ranking/distribution, media storage, reactions, comments, notifications, sharing, permissions, or UI presentation.

## Status
Architecture and implementation boundary established. Concrete domain-provider integration is intentionally deferred until the authoritative post domain exists.
