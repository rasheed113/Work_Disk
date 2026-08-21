# BOT-13 — Content/Post Blueprint

```text
Caller / Domain
      |
      v
ContentCommand
      |
      v
BOT-13 Content/Post
      |
  authority gate
      |
      v
ContentProvider
      |
      v
Opaque ContentRef
```

BOT-13 is a reusable creation boundary for post content. It does not own feed distribution, media acquisition, editing, reactions, comments, notification delivery, or ranking.

The caller supplies authority, creation scope, payload reference, visibility policy reference, and idempotency key. The provider owns persistence, identifier creation, lifecycle/versioning, deduplication, and domain-specific content semantics.
