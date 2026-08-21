# BOT-59 — Location & Geospatial Tool

Boundary: provider-backed location resolution and distance intent. It does not track users, grant location permission, own maps data, or make proximity decisions.

Attacks: location spoofing, scope leakage, stale coordinates, precision escalation, privacy leakage, replay, provider failure.

Tests validate only contract/delegation; no real user location is fabricated.