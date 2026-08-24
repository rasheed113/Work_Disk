# Work_Disk Social Architecture v1

**Status:** Foundation draft — implementation locked out until this architecture passes Attack, Boundary, Blueprint, and Contract gates.

## 1. Product boundary

The Social Web is the first product being built in Work_Disk.

The Social Web owns social interaction and communication. It does not own the future Dashboard, History, Finance, or Settings workspace pages.

The Dashboard is only a navigation destination exposed from the Social top-right area. No Social domain object, service, page property, or data model may depend on Dashboard implementation.

## 2. Primary experience

The primary experience is a mobile-first social home with an Instagram-like visual/feed experience and a WhatsApp-like inbox experience, without copying proprietary implementation or branding.

The Social Web must support a real user journey:

`Identity → Social Home → Discover/View Content → Interact → Create Content → Message → Activity → Profile`

No dummy content, fake state, or presentation-only behaviour is allowed in the production vertical slice.

## 3. Navigation contract

### Top navigation

- **Inbox 📥** — opens the user's conversations.
- **Activity shortcuts** — compact access to notifications and social activity such as likes, comments, reposts, and shares.
- **Dashboard** — top-right navigation entry only; outside Social architecture.

### Bottom navigation

Exactly four primary Social destinations exist in v1:

1. **Home 🏠**
2. **Post ➕**
3. **Video 🎬**
4. **Profile 🧑‍💼**

Future additions must enter through an explicit architecture change; they are not silently appended to the navigation.

## 4. Social domains

### Home

Owns the social feed experience:

- feed composition
- content ranking/order contract
- post/video cards
- social interaction entry points
- activity shortcut presentation
- navigation into content detail

Home does not own permanent copies of another domain's data.

### Post

Owns creation and lifecycle of photo/text-oriented posts:

- draft creation
- media attachment references
- caption/content
- visibility/audience selection
- publish
- edit/delete lifecycle
- interaction counters as read models, not ownership of interaction history

### Video

Owns video-oriented content creation and playback entry:

- video selection/upload
- processing state
- thumbnail/reference metadata
- caption
- visibility/audience
- publish lifecycle
- playback presentation

Large media bytes are not stored directly in the domain database; the domain owns media references and lifecycle state.

### Profile

Owns the Social-facing profile experience:

- profile identity presentation
- avatar/media references
- biography/about content
- user's published content view
- followers/following relationships as defined by the relationship contract
- profile visibility rules

Profile does not become a global Account/settings container.

### Inbox

Owns direct communication:

- conversations
- participants
- messages
- message delivery/read state
- attachments as references
- conversation lifecycle
- realtime updates

Inbox must have strict conversation and participant authorization boundaries.

### Activity

Owns social activity events and their presentation/read state:

- notifications
- likes
- comments
- reposts
- shares
- future activity event types

An activity event is not the source of truth for the underlying domain object. It points to the authoritative object/action that generated it.

## 5. Core entities

The architecture starts with these conceptual entities:

- User Identity
- Social Profile
- Post
- Video
- Media Asset Reference
- Comment
- Like
- Repost
- Share
- Follow Relationship
- Conversation
- Conversation Participant
- Message
- Activity Event
- Notification State

Exact persistence schemas are deferred to the relevant domain contracts.

## 6. Ownership law

Every piece of persistent data has exactly one authoritative owner.

Other pages and domains consume references/read models rather than creating competing copies.

Examples:

- Post owns post content.
- Video owns video metadata/lifecycle.
- Comment owns comment content.
- Like owns the like action.
- Conversation owns conversation membership and message ordering.
- Activity owns activity-event records, but not the underlying post/comment/message.

## 7. Page-property law

Every page owns its own page properties and page-specific functions.

If a future feature belongs to Social Home, it is added to Social Home's property/contract boundary.

If a future feature belongs to Profile, it is added to Profile's boundary.

No central catch-all page-properties object may become a dumping ground for unrelated functionality.

## 8. Provider boundary

Firebase may provide infrastructure for:

- authentication
- database/realtime data
- messaging transport
- media storage
- push notifications
- security enforcement primitives

Work_Disk owns the domain contracts. Firebase is an infrastructure adapter, not the domain model.

Conceptually:

`Social Domain → Application Contracts → Infrastructure Ports → Firebase Adapter`

This keeps the system replaceable and testable.

## 9. Security boundary

Every read/write operation must be authorized against the current authenticated identity and the relevant relationship/context.

Security rules are not treated as the only authorization layer. Application contracts and provider rules must agree.

Required invariants:

- A user cannot write another user's private content.
- A user cannot read a private conversation without membership/authority.
- Deleted/revoked content cannot silently reappear through cached/read-model state.
- Client UI state is never treated as authorization evidence.
- Provider credentials and privileged configuration never enter browser bundles.

## 10. Realtime boundary

Realtime behaviour is required for Inbox and may be used for Activity and other live social surfaces.

Realtime transport is an infrastructure concern. Domain state transitions remain authoritative independently of the transport mechanism.

## 11. Media boundary

Media lifecycle is separate from content lifecycle:

`select → upload → process → attach → publish → replace/delete according to contract`

The domain stores references and metadata, not arbitrary client-local file paths.

## 12. Architecture laws

1. **No fake functionality.** A visible action must have a real contract-backed path.
2. **No hidden ownership.** Every persistent object has one authoritative owner.
3. **No destructive context switching.** Navigation/context changes never erase unrelated user data.
4. **No provider leakage.** Firebase types do not define Social domain semantics.
5. **No UI authority.** React state is presentation state, not security authority.
6. **No silent navigation growth.** New primary navigation requires an architecture change.
7. **No catch-all page.** Page-specific properties remain inside the page boundary.
8. **No implementation before contract.** Code follows architecture gates.
9. **No dummy production data.** Empty states are explicit; fake records are prohibited.
10. **No Dashboard coupling.** Social must remain independently buildable from the future Dashboard workspace.

## 13. Build sequence

`Social Architecture → Attack → Boundary → Blueprint → Contracts → Firebase infrastructure decision → UI shell → domain vertical slices → tests → security verification → deployed verification`

The first implementation vertical slice should prove one complete real Social journey rather than building disconnected screens.
