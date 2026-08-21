# BOT-57 — Video Call Tool

Boundary: video-call invite/accept/end intent. Provider owns signalling, media transport, device access and persistence.

Attacks: spoofing, session substitution, replay, stale session, unauthorized participant, privacy leakage, provider failure, UI coupling.

Tests verify only validation/delegation; no live call is fabricated.