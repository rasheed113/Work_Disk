# BOT-56 — Audio Call Tool

Boundary: call invite/accept/end intent. Signalling, media transport, permissions, participant authority and persistence remain provider/platform responsibilities.

Attacks: spoofing, session substitution, replay, stale session, unauthorized participant, provider failure, UI coupling, privacy leakage.

Contract tests validate boundary rejection/delegation only; no live call or production session is fabricated.