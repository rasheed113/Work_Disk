# Work_Disk Social Boundary v1

**Status:** Completed.

## Boundary model

```text
Presentation
    ↓
Social Application Contracts
    ↓
Social Domain
    ↓
Infrastructure Ports
    ↓
Firebase / other providers
```

No lower layer may become an authority for a higher layer's business meaning.

## Page boundaries

### Home
**Owns:** feed query/composition, feed presentation state, discovery entry, interaction entry points.

**Does not own:** post persistence, comment persistence, conversation persistence, account settings.

### Post
**Owns:** post creation/edit/delete lifecycle and post content metadata.

**Consumes:** authenticated identity, media references, audience policy, interaction read models.

### Video
**Owns:** video content lifecycle, processing metadata, playback metadata.

**Consumes:** authenticated identity, media references, audience policy.

### Profile
**Owns:** Social profile presentation and profile-owned content views.

**Does not own:** authentication credentials, application settings, private conversation state.

### Inbox
**Owns:** conversations, membership, messages, message lifecycle and delivery/read state.

**Does not own:** global notifications or profile identity.

### Activity
**Owns:** activity events and notification/read state.

**Does not own:** the underlying post/comment/like/share/message.

## Cross-cutting boundaries

### Identity boundary
Authenticated identity is supplied to application/domain operations through an explicit authority interface. UI state is never identity authority.

### Authorization boundary
Authorization decisions require authenticated identity plus the relevant resource relationship/context.

### Media boundary
Content domains receive provider-neutral media references. Upload/storage implementation remains infrastructure.

### Realtime boundary
Realtime providers deliver events. Domain state transitions remain authoritative.

### Notification boundary
Notification generation consumes domain events/actions. It cannot mutate unrelated source entities as a side effect of rendering.

### Search/discovery boundary
Search results are read models. Search does not become authoritative ownership of indexed content.

## Firebase boundary

Firebase adapter responsibilities may include:

- Firebase Authentication integration
- Firestore/realtime persistence adapters
- Cloud Storage adapter
- push notification integration
- provider security rule deployment
- provider-specific serialization

The adapter must not contain product rules that should be shared across infrastructure implementations.

## Client boundary

The browser owns:

- rendering
- navigation
- local ephemeral UI state
- optimistic presentation state where explicitly permitted

The browser does not own:

- authorization truth
- persistent ownership
- privileged Firebase credentials
- security policy decisions

## Data flow rule

A normal read follows:

`UI → application read contract → authorized domain/infrastructure query → authoritative/read-model result → UI`

A normal write follows:

`UI → application command → identity/authorization validation → domain state transition → persistence → result/event → UI`

## Realtime read rule

`UI → authorized realtime subscription → provider adapter → domain/read-model events → UI`

A subscription is not authorization by itself.

## Boundary violations

The following are architecture violations:

- Firebase SDK imports in domain models.
- Direct database calls from React components.
- UI-only authorization.
- Activity records used as primary entity storage.
- Shared catch-all page property ownership.
- Dashboard-specific logic inside Social domains.
- Permanent domain identity based on local device paths.

## Boundary conclusion

Social ownership, infrastructure, presentation, identity, authorization, media, realtime, and activity boundaries are explicitly separated.

**Next gate:** Blueprint v1.
