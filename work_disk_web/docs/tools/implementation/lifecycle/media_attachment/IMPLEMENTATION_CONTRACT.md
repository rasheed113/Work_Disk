# BOT-15 — Media/Attachment Implementation Contract

BOT-15 manages the attachment relationship between an authorised owner/scope and an opaque media reference. It does not upload bytes, transcode media, generate thumbnails, scan content, or decide visibility.

Mandatory inputs: request identity, authority reference, attachment scope, owner reference, media reference, bounded operation, idempotency key, expected version.

Operations: Attach and Detach.

The caller supplies authority. The provider owns media identity, storage, lifecycle, metadata, attachment persistence, CAS and replay semantics. Media bytes remain outside this tool.

No page, domain, media MIME type, storage backend, permission rule, feed rule or notification rule is hardcoded.
