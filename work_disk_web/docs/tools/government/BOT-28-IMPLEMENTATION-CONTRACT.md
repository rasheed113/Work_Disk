# BOT-28 Implementation Contract

Inputs: request_id, authority_reference, actor_reference, service_reference, operation, payload_reference.

Guarantees: required references are validated before provider delegation; SUBMIT requires payload; BOT-28 does not approve, deny, assign, or mutate a case directly.

Non-responsibilities: eligibility, workflow decisions, case management, document verification, notifications and permissions.