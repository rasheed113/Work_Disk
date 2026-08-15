# BOT-01 — Profile

## Identity

- **Bot ID:** BOT-01
- **Domain:** Account
- **Category:** Account Bot
- **Status:** Completed

## Purpose

BOT-01 provides the foundational Account authentication and identity
capabilities required by Work_Disk.

## Primary Responsibility

BOT-01 owns the concrete Account authentication foundation defined by its
approved architecture and implementation contract.

## Owns

- Account authentication foundation
- Account authentication identity boundary defined by BOT-01
- Credentials and authentication-related persistence defined by BOT-01
- Session behaviour defined by BOT-01
- Validation required by its approved contract

## Consumes

BOT-01 may consume only the dependencies explicitly authorised by its
architecture and implementation contract.

## Does Not Own

BOT-01 does not become the authority for future Account features merely
because they may depend on Account identity or authentication.

BOT-01 does not own the Profile Authority.

BOT-01 does not own unrelated domain systems.

## Relationship With BOT-02

BOT-02 is the Profile Authority and Profile Assembly Point.

BOT-02 may consume Account/Profile identity references supplied through the
authorised Account architecture.

BOT-01 remains responsible for its own Account and authentication boundary.

## Architecture Boundary

Completion of BOT-01 does not automatically authorise implementation of
future Account bots or features.

Any behaviour outside the approved BOT-01 architecture and implementation
contract requires its own architectural authority.

## Implementation Record

Authoritative implementation documentation remains under:

`docs/account/implementation/bot-01/`

This profile is an identity and boundary record, not a replacement for the
BOT-01 Blueprint, Implementation Contract, or Completion Record.

## Status

BOT-01 implementation is completed according to its recorded completion
boundary.

Future changes must not silently expand BOT-01 beyond its approved
architectural responsibility.
