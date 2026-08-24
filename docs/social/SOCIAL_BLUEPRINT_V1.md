# Work_Disk Social Blueprint v1

**Status:** Completed.

## 1. Product shell

### Top bar

```text
[📥 Inbox]   [Social identity / title]   [Activity shortcuts]   [→ Dashboard]
```

Activity shortcuts are compact and expandable without becoming primary navigation.

### Main surface

The Home surface is a vertically scrollable social feed. Feed cards are content-type aware and expose only interactions permitted by the content policy.

### Bottom navigation

```text
[🏠 Home] [➕ Post] [🎬 Video] [🧑‍💼 Profile]
```

Exactly four primary destinations in v1.

## 2. Social Home blueprint

Components:

- `SocialHeader`
- `InboxShortcut`
- `ActivityShortcutRail`
- `Feed`
- `PostCard`
- `VideoCard`
- `InteractionBar`
- `BottomSocialNavigation`

Home page properties belong under Home and may include feed mode, pagination cursor, refresh state, and local presentation preferences.

## 3. Post blueprint

Flow:

`Create draft → attach media/text → audience policy → validate → publish → authoritative result → feed/read model update`

Required states:

- draft
- validating
- publishing
- published
- failed
- deleted according to lifecycle contract

## 4. Video blueprint

Flow:

`Select video → upload → processing → metadata/caption → audience policy → publish → playback/read model`

Processing is asynchronous. UI must expose processing state instead of pretending a video is immediately ready.

## 5. Profile blueprint

Profile surface contains:

- avatar
- display identity
- biography/about
- relationship actions
- published content tabs/read models
- profile-owned social information

Profile editing and profile reading use explicit commands/queries rather than direct persistence from components.

## 6. Inbox blueprint

### Conversation list

Shows authorized conversations with:

- participant summary
- latest message preview
- timestamp
- unread state

### Conversation view

Contains:

- message timeline
- composer
- attachment entry
- delivery/read indicators where supported
- realtime updates

### Messaging flow

`Compose → authorize → persist message → acknowledge → publish realtime event → update conversation read model`

## 7. Activity blueprint

Activity shortcut categories:

- Notifications
- Likes
- Comments
- Reposts
- Shares

Activity detail is a read-oriented surface with navigation back to the authoritative object when permitted.

## 8. Domain modules

Initial logical module structure:

```text
social/
  home/
  post/
  video/
  profile/
  inbox/
  activity/
  relationships/
  media/
  identity/
  authorization/
```

Each module owns its contracts and tests.

## 9. Infrastructure modules

```text
infrastructure/
  firebase/
    auth/
    database/
    storage/
    realtime/
    notifications/
```

Infrastructure exposes adapters to the application layer rather than leaking provider objects into UI/domain code.

## 10. First vertical slice

The first implementation should prove:

`authenticated user → Home → create Post → persist real Post → return to Home → display authoritative Post → Like → Activity entry`

This slice deliberately proves identity, authorization, persistence, media/content ownership, feed read, interaction, and activity without requiring the complete product.

## 11. Future extension rule

New functionality is added to the owning page/domain:

- Home feature → Home boundary
- Post feature → Post boundary
- Video feature → Video boundary
- Profile feature → Profile boundary
- Inbox feature → Inbox boundary
- Activity feature → Activity boundary

Only cross-domain functionality receives a shared contract.

## 12. UI quality principles

The visual direction is premium, modern, social-first, mobile-first, and interaction-rich. The product may take inspiration from familiar social interaction patterns while maintaining its own Work_Disk identity.

No UI polish is allowed to conceal missing functionality.

## Blueprint conclusion

The Social product has a concrete page shell, navigation model, domain module map, infrastructure map, and first real vertical slice.

**Next gate:** Contracts v1.
