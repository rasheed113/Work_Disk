# BOT-15 — Media/Attachment Blueprint

```text
Caller/Domain -> MediaCommand -> Authority Gate -> MediaProvider -> Opaque Attachment Ref
```

Reusable across posts, profiles, documents, chat and future domains. Media acquisition/storage is a separate capability; BOT-15 only governs the attachment relationship.

## Roadmap
- integrate authoritative media store
- add concrete CAS/idempotency tests
- connect Content/Post through opaque attachment references
- connect Chat/Documents later without absorbing their lifecycle rules

## README / Completion
BOT-15 is an authority-gated attachment boundary. Concrete storage integration is intentionally deferred until the authoritative media store exists.
