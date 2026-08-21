# Phase 4 — BOT-51 to BOT-54 Architecture & Contract Lock

Status: LOCKED FOR IMPLEMENTATION
Date: 2026-08-21

## Purpose
This document freezes the boundaries for the four new Tool-Bot candidates identified by the Phase 3 missing-capability audit. It is a design gate; it does not implement platform/device backends.

## BOT-51 — Device Access Tool

### Purpose
Reusable boundary for requesting and observing access to device capabilities such as camera, microphone, location and media-library access.

### Owns
- Access request intent
- Capability identifier
- Caller/context reference
- Platform result normalisation
- Access-state observation

### Does not own
- Account identity
- Permission policy/authority issuance
- Platform storage encryption keys
- Camera capture itself
- Gallery selection
- Domain data mutation

### Contract invariants
1. Every request carries an authenticated caller/context reference.
2. Capability names are explicit and finite; unknown capabilities are rejected.
3. A denial is an outcome, not destruction of prior evidence/state.
4. The tool cannot silently grant access.
5. Platform-specific results are normalised without inventing success.
6. Device access state cannot mutate domain ownership.

### Attack set
Spoofed caller; capability escalation; silent grant; stale permission state; cross-account leakage; replay; platform-result forgery; denial-as-destruction; device substitution; background privilege escalation; UI coupling; policy leakage; unknown capability injection; race between request and state observation; boundary drift.

## BOT-52 — Media Acquisition Tool

### Purpose
Reusable acquisition boundary for selecting or capturing media from device capabilities.

### Owns
- Acquisition intent
- Source selection (camera/gallery/device picker)
- Selection constraints
- Candidate media references
- Acquisition result normalisation

### Does not own
- Device permission authority
- Media persistence
- Upload/transfer
- Transcoding
- Domain attachment ownership
- Deletion

### Contract invariants
1. Acquisition requires caller/context authority.
2. Permission is checked through the device-access boundary; it is not granted here.
3. Returned media references identify acquired candidates, not persisted domain ownership.
4. Cancel/deny is a valid non-destructive outcome.
5. No acquisition result may fabricate a media object that the provider did not return.
6. Acquisition cannot mutate domain records.

### Attack set
Permission bypass; fake media reference; cross-account media leakage; path traversal; malicious MIME/type claims; oversized input; duplicate acquisition; replay; stale picker state; camera/gallery source confusion; cancellation loss; persistence coupling; upload coupling; UI coupling; boundary drift.

## BOT-53 — QR Tool

### Purpose
Reusable QR encode/decode boundary for Work_Disk payload envelopes.

### Owns
- QR encode intent
- QR decode intent
- Payload envelope validation
- Format/version validation
- Decode result normalisation

### Does not own
- Identity creation
- Account authority
- Authentication
- Permission grants
- Domain mutation
- Trust establishment

### Contract invariants
1. QR data is treated as untrusted input.
2. Envelope version/type must be explicit and validated.
3. Decoding does not imply trust or authorization.
4. Invalid/unsupported payloads are rejected without domain mutation.
5. Identity references remain references; BOT-53 never generates authoritative IDs.
6. Replay protection belongs to the consuming protocol, not to QR encoding itself.

### Attack set
Payload tampering; malicious payload type; oversized payload; parser confusion; version downgrade; replay; identity spoofing; authority confusion; encoded injection; truncation; duplicate scan; cross-context payload use; UI coupling; decoder resource exhaustion; boundary drift.

## BOT-54 — i18n / Translation Tool

### Purpose
Reusable translation/localisation generation and validation boundary for Work_Disk language resources.

### Owns
- Translation request
- Source/target language references
- Resource-key validation
- Placeholder/plural consistency validation
- Translation result normalisation
- Registry-compatible resource generation

### Does not own
- User language preference authority
- UI rendering
- Account identity
- Locale policy
- Translation of arbitrary secrets/private data without explicit caller authority

### Contract invariants
1. Source and target language identifiers must be explicit and registry-valid.
2. Translation keys remain stable; the tool cannot silently rename domain keys.
3. Placeholders and required interpolation parameters must be preserved/validated.
4. Missing translations are explicit outcomes, never fabricated success.
5. Generated resources are versioned and attributable to their source input.
6. RTL metadata is preserved where the language registry requires it.

### Attack set
Language spoofing; key injection; placeholder corruption; plural-rule corruption; silent fallback; stale translation overwrite; source/target inversion; registry mismatch; private-data leakage; malicious resource content; encoding corruption; RTL metadata loss; version confusion; bulk-resource corruption; boundary drift.

## Cross-BOT dependency rules
- BOT-51 is the device-access gate used by BOT-52; BOT-52 cannot grant permission.
- BOT-52 produces candidate media references; existing media/upload/transfer tools own subsequent persistence or delivery.
- BOT-53 may be called by identity, verification, relationship or service workflows, but QR decoding never grants authority.
- BOT-54 consumes the canonical language registry and must preserve registry/version semantics; UI remains a consumer.
- BOT-50 Tool Registry/Dispatcher registers and routes these tools but does not absorb their domain boundaries.

## Implementation gate
Implementation may begin only against these locked boundaries. No production platform backend, permission policy, identity generation, media persistence, trust establishment, or UI ownership may be introduced by these four Tool-Bots merely for convenience.

## Decision
BOT-51, BOT-52, BOT-53 and BOT-54 are approved as independent Tool-Bot boundaries. Location/Geospatial and Document Preview/Conversion remain deferred architecture candidates and are not promoted into BOT numbers by this contract.
