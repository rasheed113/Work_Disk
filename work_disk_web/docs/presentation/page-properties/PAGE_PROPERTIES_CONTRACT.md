# Work_Disk — Page Properties Contract

## Status
DESIGNED / CONTRACT LOCKED

## Purpose
Define reusable page-level properties that expose existing authoritative Tool-Bot capabilities without moving authority into a page or Dashboard.

## Core Rule
A page property is a presentation capability declaration. It is not a BOT, business rule, permission authority, or data source.

## Flow
Role/Capability/Context
→ Page Property Registry
→ Dedicated Tool-Bot contract
→ Authoritative read/write path
→ Shared transport where required
→ Page Presentation Adapter
→ UI

## Reusable Properties
- `search` → Search Tool-Bot
- `filter` → Filter Tool-Bot
- `sort` → Sort Tool-Bot
- `selection` → Mark/Unmark Tool-Bot
- `actions` → Action Board / applicable action BOTs
- `edit` → Edit Tool-Bot
- `delete` → Delete Tool-Bot
- `share` → Share/Repost capability
- `save` → Save/Bookmark capability
- `notifications` → Notification Tool-Bot
- `media` → Media access/acquisition capability
- `more` → capability registry; contains only capabilities actually available in the current context

## Availability
A property may be `AVAILABLE`, `HIDDEN`, or `UNAVAILABLE`.
- `AVAILABLE`: current page/context may expose the property and its authoritative BOT path exists.
- `HIDDEN`: capability exists but current role/context must not expose it.
- `UNAVAILABLE`: capability is not connected/available; UI must not fabricate behaviour.

## Non-Goals
- no page-local business logic;
- no duplicate Tool-Bots;
- no fake handlers;
- no invented permissions;
- no hardcoded domain data;
- no destructive removal of domain data when a property is hidden.

## Role Rule
Role/capability/permission authority decides whether a property can be used. The page registry only declares which reusable property maps to which existing Tool-Bot capability.

## Page-Specific Extension
A page may add a property only when an authoritative BOT contract exists. Page-specific properties must use a page-specific presentation adapter and must not become generic global properties without architecture review.
