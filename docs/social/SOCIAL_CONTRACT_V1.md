# Work_Disk Social Contract v1

**Status:** Implementation contract — v1.

## 1. Contract objective

Define the minimum provider-neutral interfaces required to implement the first Social vertical slice without violating the architecture or boundaries.

## 2. Identity contract

Every application command/query receives an authenticated identity context from an authority boundary.

Minimum conceptual value:

```text
AuthenticatedIdentity
- userId
- sessionId/context
- authentication state
```

Rules:

- missing/invalid identity rejects protected operations;
- UI cannot manufacture identity authority;
- provider-specific auth objects terminate at the infrastructure adapter.

## 3. Post command contract

Conceptual command:

```text
CreatePost
- actorId
- content
- mediaReferences[]
- audience
```

Preconditions:

- actor is authenticated;
- actor is authorized to publish;
- content satisfies validation rules;
- every media reference is valid for the actor/context.

Result:

```text
CreatePostResult
- postId
- publishedAt
- status
```

Failure must be explicit and must not fabricate a published post.

## 4. Post query contract

```text
GetHomeFeed
- actorId
- cursor?
- limit
```

The result is an ordered read model containing authoritative post identifiers and the fields required by Home presentation.

The query must not return content the actor is unauthorized to see.

## 5. Like contract

```text
LikePost
- actorId
- postId
```

The operation is idempotent for the same actor/post pair.

Unliking is a separate explicit command or a contract-defined inverse operation; it must not be inferred from UI state alone.

## 6. Activity contract

Domain actions may emit activity events:

```text
ActivityEvent
- eventId
- type
- actorId
- targetReference
- createdAt
```

Activity consumers may render these events but must not use them as authoritative storage for the underlying target.

## 7. Comment contract

```text
CreateComment
- actorId
- postId
- content
```

The command requires actor authorization and target visibility permission.

## 8. Repost contract

```text
Repost
- actorId
- postId
```

The original post remains authoritative. A repost is a distinct action/reference.

## 9. Share contract

```text
Share
- actorId
- targetReference
- destination/context
```

Sharing creates an explicit action record where required; it does not duplicate the target content as a new authoritative post.

## 10. Relationship contract

```text
Follow
- actorId
- targetUserId
```

Relationship changes require authorization and must preserve both users' independent data ownership.

## 11. Inbox contract

### Conversation creation

```text
CreateConversation
- actorId
- participantIds[]
```

### Send message

```text
SendMessage
- actorId
- conversationId
- content
- attachmentReferences[]
```

Preconditions:

- actor is authenticated;
- actor is an authorized participant;
- attachment references are authorized;
- message content is valid.

Result includes authoritative `messageId`, timestamp, and status.

## 12. Realtime contract

Realtime subscriptions require authorization equivalent to the underlying read operation.

Realtime delivery is at-least observational; the application must not treat receipt of an event as proof of persistence success.

The authoritative write result comes from the command/persistence path.

## 13. Media contract

```text
MediaReference
- mediaId
- ownerId
- type
- providerReference
- lifecycleStatus
```

Provider reference values are opaque to domain logic.

## 14. Firebase adapter contract

Firebase adapters translate between Work_Disk contracts and provider operations.

Examples:

```text
FirebaseAuthAdapter
FirebasePostRepository
FirebaseFeedRepository
FirebaseConversationRepository
FirebaseMessageRepository
FirebaseMediaStorage
FirebaseRealtimeAdapter
FirebaseNotificationAdapter
```

Adapters must not redefine domain authorization or ownership semantics.

## 15. Error contract

Protected operations return explicit categories conceptually equivalent to:

- `UNAUTHENTICATED`
- `UNAUTHORIZED`
- `NOT_FOUND`
- `VALIDATION_FAILED`
- `CONFLICT`
- `MEDIA_NOT_READY`
- `PROVIDER_FAILURE`
- `INTERNAL_FAILURE`

No generic successful fallback is permitted.

## 16. Empty state contract

An empty feed means no authorized content was returned. It must not be filled with fake posts.

An empty inbox means no authorized conversations were returned.

An unavailable profile must remain explicitly unavailable rather than being replaced with fabricated profile data.

## 17. Page contract

Every page exposes only its own page-specific properties/functions.

Shared UI primitives may be reused, but ownership remains with the page/domain that defines the behaviour.

## 18. Navigation contract

Bottom navigation v1 is immutable:

`Home | Post | Video | Profile`

Inbox and Activity are top-level shortcuts. Dashboard is a top-right external destination.

## 19. Testing contract

Before a Social feature is considered complete:

1. domain contract tests pass;
2. authorization tests pass;
3. persistence adapter tests pass;
4. realtime/security tests pass where applicable;
5. presentation tests pass;
6. production build passes;
7. deployed runtime verification proves the real data path.

## 20. Implementation gate

No production feature may bypass this contract by directly calling Firebase from a presentation component.

The first implementation target is the vertical slice defined in the Blueprint:

`Identity → Home → Create Post → Persist → Home read → Like → Activity`

## Contract conclusion

Social v1 is now defined sufficiently to begin implementation without inventing ownership, navigation, authorization, or provider semantics during coding.
