# BOT-51 — Device Access Tool

## Implementation
BOT-51 validates the request envelope and delegates device access request/observation to a provider. The implementation contains no platform permission backend and cannot grant access itself.

## Boundary
Owns request intent, finite capability selection, caller/context reference and provider-result normalization. It does not own permission authority, account identity, storage encryption keys, capture, gallery selection or domain mutation.

## Verification
Contract tests cover request delegation, observation delegation and missing caller-context rejection. The provider is a test double only; no production device-access outcome is hardcoded into the tool.

## Attack coverage
Caller spoofing, capability escalation, silent grant, stale state, cross-account leakage, replay, forged platform result, denial-as-destruction, device substitution, background privilege escalation, UI coupling, policy leakage, unknown capability, request/observation race and boundary drift are addressed by the locked contract and provider boundary.
