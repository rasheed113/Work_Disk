# BOT-23 Implementation Contract

## Inputs
request_id, authority_reference, reporter_reference, target_reference, reason_code, optional context_reference.

## Guarantees
Invalid requests are rejected before provider execution. Valid requests are delegated without changing target state. Provider results are returned without inventing enforcement outcomes.

## Non-responsibilities
No deletion, moderation decision, suspension, blocking, ranking, notification or permission grant.
