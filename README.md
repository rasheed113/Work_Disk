# Work_Disk

Work_Disk is a modern social web platform with posts, video, messaging, profiles, notifications, and a future productivity workspace.

## Current build boundary

The first product boundary is the **Social Web**. Dashboard is intentionally outside the Social product architecture; it is exposed only as a top-right navigation entry until the Social product is complete.

## Social navigation

### Top bar
- Inbox 📥 — top-left
- Social header actions — notifications and activity shortcuts
- Dashboard — top-right

### Bottom navigation
- Home 🏠
- Post ➕
- Video 🎬
- Profile 🧑‍💼

## Activity shortcuts

The social home may expose compact activity shortcuts for:

- Notifications
- Likes
- Comments
- Reposts
- Shares
- Future activity types added through the Social contract

## Architecture workflow

`Architecture → Attack → Boundary → Blueprint → Contract → Implementation → Tests → Verification`

Implementation does not begin until the relevant contract is defined.

## Firebase

Firebase is a candidate infrastructure platform for authentication, realtime messaging, data, media storage, notifications, and security rules. Firebase services remain behind Work_Disk domain boundaries so the product architecture is not coupled directly to provider-specific APIs.
