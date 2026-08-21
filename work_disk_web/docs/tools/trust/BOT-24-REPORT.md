# BOT-24 — Block / Mute Tool

## Boundary
BOT-24 records an authorised actor's block or mute relationship against a target. Block and mute are separate operations. It does not delete, report, moderate, suspend, grant authority, or mutate target content.

## Contract
The caller supplies request, authority, actor, target and operation references. Validation occurs before provider delegation. Provider owns persistence, conflict policy and relationship state.

## Integration
BOT-24 may be called from profiles, posts, comments, messages and other authorised surfaces. Downstream feed, messaging and notification behaviour consumes the resulting relationship state rather than being implemented here.