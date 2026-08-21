# BOT-28 — Service Request / Intake Tool

Boundary: accepts an authorised actor's service-request intake intent and delegates persistence/workflow creation to a provider. It does not decide eligibility, approve requests, manage cases, or grant authority.

Attacks: missing authority, actor spoofing, service omission, payload omission, replay, duplicate submission, cross-account leakage, cross-context confusion, forged case references, provider failure, stale state, permission escalation, workflow bypass, UI coupling, oversized input, malformed references, boundary drift.

Contract: request_id, authority_reference, actor_reference and service_reference are required. SUBMIT requires payload_reference. Provider owns persistence and case/workflow semantics.

Implementation and contract-test sources are included. Native CI status is only reported when a workflow run is independently verified.
