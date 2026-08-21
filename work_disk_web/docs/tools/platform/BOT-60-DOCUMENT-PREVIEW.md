# BOT-60 — Document Preview / Conversion Tool

Boundary: provider-backed document preview and conversion intent. It does not own source storage, upload/download, document authority, or content policy.

Attacks: document substitution, format confusion, stale content, data leakage, unsafe conversion, replay, provider failure, UI coupling.

Tests validate contract/delegation only; no production documents are fabricated.