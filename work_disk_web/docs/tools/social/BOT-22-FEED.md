# BOT-22 — Feed Tool

Reusable authority-gated feed assembly/read boundary. The caller supplies viewer authority, viewer reference, feed scope, cursor and bounded page size. Provider owns eligibility, social-graph integration, ranking and persistence/index details. BOT-22 does not grant access, mutate posts, perform reactions, or become the social graph.

Attack focus: cross-account leakage, scope confusion, authority omission, ranking-as-authority, pagination cursor tampering, unbounded limits, duplicate items, stale visibility, deleted content, provider failure, personalization leakage, and boundary drift.
