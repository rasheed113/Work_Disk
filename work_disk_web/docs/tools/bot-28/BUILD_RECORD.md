# BOT-28 — Service Request / Intake Tool

Official name: Service Request / Intake Tool

Boundary: accepts an authorised actor's service request intent and delegates persistence/workflow handling to a provider. It does not decide government/service authority, approve cases, perform workflow transitions, or own records.

Attack register: missing authority; actor spoofing; service omission; payload omission; malformed references; replay; duplicate submission; withdrawal confusion; cross-account leakage; cross-role confusion; scope escalation; provider rejection; provider failure; stale state; UI coupling; authority substitution; boundary drift.

Implementation contract: request_id, authority_reference, actor_reference, service_reference, operation, payload_reference. Required references are validated before provider delegation. Provider owns persistence and domain workflow semantics.

Tests: contract-test source covers valid delegation and invalid required-field rejection.

Documentation: this record is the implementation/build record for BOT-28.