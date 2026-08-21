# BOT-30 Implementation Contract

## Inputs
request_id, authority_reference, actor_reference, record_reference (when required), payload_reference (for create/update), operation.

## Guarantees
Validation occurs before provider execution. The tool delegates persistence rather than owning storage. Operations remain explicit and do not silently translate archive into delete or restore into permission grant.

## Non-responsibilities
No authentication, permission issuance, retention-policy decision, evidence certification, moderation, notification or UI behavior is implemented by BOT-30.