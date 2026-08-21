# BOT-23 — Report Tool

## Boundary
BOT-23 records a user-authorized report about a target. It does not delete, moderate, suspend, block, grant authority, or mutate the reported target.

## Contract
The caller supplies request, authority, reporter, target and reason references. Validation happens before provider delegation. The provider owns persistence, duplicate policy, moderation queue routing and evidence retention.

## Attack focus
Authority omission; reporter spoofing; target omission; reason tampering; cross-account leakage; report-as-enforcement; duplicate/replay handling; provider failure; sensitive context leakage; stale target context; UI coupling; and boundary drift.

## Integration
BOT-23 may be called from posts, comments, profiles, media, messages and other authorised surfaces. Enforcement remains a separate capability.
