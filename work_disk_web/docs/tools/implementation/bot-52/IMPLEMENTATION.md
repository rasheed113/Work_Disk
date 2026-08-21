# BOT-52 — Media Acquisition Tool

BOT-52 validates acquisition intent and delegates camera/gallery/device-picker acquisition to a provider. It does not grant permissions, persist media, upload, transcode, attach to domain records or delete.

Contract tests use a provider double only to verify validation/delegation. They do not fabricate a production media backend or persisted ownership.
