# BOT-06 — Archive 📦 Tool Bot Profile

**Number:** 06  
**Name:** Archive  
**Category:** Lifecycle Tool Bot  
**Call model:** Multi-caller / domain-neutral

## Role
Own the generic archive/unarchive lifecycle after an authorised caller supplies authority and target context.

## Typical callers
Inbox, Chat, Post, Notification, Document, Fleet/Entry, and future domain bots.

## Does not own
Domain policy, permissions, notifications, retention, deletion, trash, UI, search, marking, sorting, or cascade semantics.

## Safety posture
Fail closed on missing authority, malformed references, stale versions, lifecycle conflicts, and unconfirmed execution.

## Emoji
User-facing representations may use the real colourful `📦` emoji. Core code semantics do not depend on emoji text.
