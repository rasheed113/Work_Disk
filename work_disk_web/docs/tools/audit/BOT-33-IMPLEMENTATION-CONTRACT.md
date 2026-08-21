# BOT-33 Implementation Contract

## Input
An Event containing event identity, request identity, authority, actor, subject, event type, evidence reference, occurrence time and monotonic sequence value.

## Guarantees
Required references and temporal values are validated before provider delegation. BOT-33 delegates persistence and authoritative conflict handling to the provider.

## Non-responsibilities
No authentication, permission grant, moderation decision, deletion, historical mutation, evidence storage, retention decision or UI behaviour.

## Invariant
An accepted call represents append intent only; it does not imply that durable persistence succeeded unless the provider result says so.