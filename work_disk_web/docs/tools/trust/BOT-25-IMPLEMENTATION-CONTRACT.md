# BOT-25 Implementation Contract

## Inputs
request_id, authority_reference, moderator_reference, target_reference, policy_reference, action_reference.

## Guarantees
Required references are validated before provider delegation. BOT-25 never treats moderation capability as general account authority.

## Non-responsibilities
No identity issuance, permission grant, arbitrary deletion, blocking, reporting, ranking, or notification side effect.