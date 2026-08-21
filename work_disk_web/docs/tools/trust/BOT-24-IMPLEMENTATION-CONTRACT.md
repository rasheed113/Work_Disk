# BOT-24 Implementation Contract

## Inputs
request_id, authority_reference, actor_reference, target_reference, operation (BLOCK or MUTE), optional expected_version.

## Guarantees
Required references are validated before provider delegation. Block and mute remain distinct operations. BOT-24 does not mutate the target itself and does not grant permission.

## Non-responsibilities
No deletion, reporting, moderation decision, notification, ranking, permission grant, or content mutation.