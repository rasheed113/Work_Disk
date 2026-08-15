# TOOL-BOT-03 — Profile

## Identity

- **Bot ID:** TOOL-BOT-03
- **Domain:** Tools
- **Category:** Identifier Generation Tool
- **Status:** Completed

## Purpose

TOOL-BOT-03 provides reusable identifier generation and validation for
Work_Disk.

It is a shared Tool capability, not a domain authority.

## Primary Responsibility

TOOL-BOT-03 generates identifier candidates according to the approved
identifier policies and exposes the guarded public Result API.

## Supported Identifier Classes

- Account ID
- Entry ID
- Fleet ID

## Identifier Rules

- Account ID: exactly 9 characters
- Entry ID: exactly 11 characters
- Fleet ID: exactly 7 characters
- Approved identifiers use the authorised alphanumeric representation
- Account ID generation uses cryptographically secure randomness
- Generation mode is not encoded as online or offline

## Owns

- Identifier candidate generation
- Supported identifier policy enforcement
- Identifier format validation
- Public Result API defined by TOOL-BOT-03
- Generation behaviour defined by its approved implementation contract

## Consumers

Authorised consumers may request identifier candidates through the
TOOL-BOT-03 public contract.

The Tool remains independent of the domain authority of its consumers.

## Does Not Own

TOOL-BOT-03 does not own:

- Account creation
- Entry creation
- Fleet creation
- Account, Entry, or Fleet domain authority
- Authoritative identifier persistence
- Authoritative synchronisation
- Domain ownership
- Authentication
- Permissions
- Business-domain services

## Authority Boundary

TOOL-BOT-03 generates identifier candidates only.

A generated identifier must not be presented as authoritative global uniqueness
merely because the generator produced it.

Authoritative persistence, synchronisation, collision detection, and domain
authority remain with the appropriate external layer.

For Account IDs, authoritative persistence must enforce uniqueness. If a
collision is detected, the generator may produce another candidate or return
an explicit failure according to its contract.

For Entry IDs, accidental collision remains detectable by the authoritative
persistence or synchronisation layer.

For Fleet IDs, creation, ownership, persistence, and authority remain outside
TOOL-BOT-03.

## Validation Boundary

TOOL-BOT-03 provides validation required by its identifier policies and
public Result API.

Validation does not grant the Tool authority over the underlying domain
record.

## Result API Boundary

The public Result API is the guarded consumer-facing boundary.

Consumers must use the approved public contract rather than depending
directly on internal generator, policy, randomness, or validation components.

## Generation Boundary

TOOL-BOT-03 does not implement separate online/offline generation modes.

The generation mechanism is shared across supported identifier classes while
their individual authority rules remain distinct.

## Architecture Boundary

TOOL-BOT-03 must remain a reusable identifier-generation Tool.

It must not expand into an Account, Entry, Fleet, authentication, permission,
or business-domain service.

Any behaviour outside the approved TOOL-BOT-03 architecture and
implementation contract requires its own architectural authority.

## Implementation Record

Authoritative implementation documentation remains under:

`docs/tools/implementation/tool-bot-03/`

Additional authoritative records include:

- `docs/tools/tool-bot-03-id.md`
- `docs/tools/tool-bot-03-result-api-final.md`

This profile is an identity and boundary record, not a replacement for the
TOOL-BOT-03 Blueprint, Implementation Contract, or Result API Final Record.

## Status

TOOL-BOT-03 implementation and its guarded Result API baseline are completed
according to the recorded completion boundary.

Future changes must not silently expand TOOL-BOT-03 beyond its approved
architectural responsibility.
