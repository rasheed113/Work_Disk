# BOT-58 — Call Signalling Tool

Boundary: provider-backed signalling intent for an existing call session. It does not authenticate participants, grant permissions, transport media, or persist call records.

Attacks: session spoofing, signal injection, replay, stale session, cross-context leakage, provider failure, UI coupling.

Contract tests cover validation/delegation only.