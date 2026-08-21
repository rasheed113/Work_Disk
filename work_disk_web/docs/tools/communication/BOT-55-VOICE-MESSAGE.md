# BOT-55 — Voice Message Tool

Boundary: validates a voice-message send intent and delegates transport/persistence to a provider. It does not capture audio, grant device permissions, own storage, or define chat policy.

Attacks: spoofed caller, missing media, cross-context leakage, replay, duplicate send, stale media, provider failure, persistence failure, unauthorized recipient, UI coupling.

Contract: request, caller context and media reference are required before provider delegation. Tests validate boundary behaviour only; no production messages are fabricated.