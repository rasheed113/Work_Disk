# BOT-16 Implementation Contract

Inputs MUST include request_id, authority_reference, delivery_scope_reference, recipient_reference, event_reference, idempotency_key, expected_version and payload_reference. The tool MUST validate before authority evaluation; rejected authority MUST prevent provider invocation. Provider owns transport and persistence. The tool MUST NOT grant permission or mutate domain state.
