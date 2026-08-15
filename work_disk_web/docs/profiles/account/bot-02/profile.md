# BOT-02 — Profile

## Identity

- **Bot ID:** BOT-02
- **Domain:** Account
- **Category:** Account Bot
- **Status:** Completed

## Purpose

BOT-02 is the Profile Authority and Profile Assembly Point for Work_Disk.

It assembles, manages, and exposes the complete persistent profile state
belonging to an authenticated account while preserving strict boundaries
between profile authority and external systems.

## Primary Responsibility

BOT-02 owns the authoritative profile assembly domains defined by its
approved architecture and implementation contract.

## Owns

- Core profile attributes
- Profile existence state
- Profile completion state
- Profile completion percentage
- Missing-profile requirements
- Profile completion suggestions
- Current profile media references
- Historical profile media references
- Historical shared-content references exposed through the profile
- Profile-related privacy state and references required for assembly
- Profile business operations explicitly authorised by BOT-02

## Consumes

BOT-02 may consume authorised inputs including:

- Authenticated account identity
- Validated principal information
- Account/Profile ID references
- Authorised media references
- Social/Post content references
- Privacy decision results
- Advisory profile-completion information

## Does Not Own

BOT-02 does not own:

- Account creation
- Identity creation
- ID generation
- Hardware media capture
- Permanent deletion engines
- The authoritative privacy decision
- Dashboard feed processing
- Unrelated external tools or systems

## Privacy Boundary

BOT-02 maintains profile-related privacy state and references required
to assemble the profile.

The authoritative privacy decision belongs to the Privacy system.

Protected profile information must not be exposed before the authorised
privacy decision has been applied.

## Media Boundary

Replacing current profile media does not silently delete previous media.

Previous profile media remains available as historical profile media
according to the authorised lifecycle.

Permanent deletion remains outside BOT-02.

## Intelligence Boundary

Shared Intelligence may provide advisory profile-completion or improvement
information.

It must never silently modify authoritative BOT-02 profile state and must
not bypass privacy authority.

## Relationship With BOT-01

BOT-02 may consume authenticated identity and validated principal
information supplied through the authorised Account architecture.

BOT-01 remains responsible for its own authentication boundary.

BOT-02 remains responsible for the Profile Authority and Assembly boundary.

## Architecture Boundary

BOT-02 must not become a dumping ground for unrelated tools or systems.

Any behaviour outside the approved BOT-02 architecture and implementation
contract requires its own architectural authority.

## Implementation Record

Authoritative implementation documentation remains under:

`docs/account/implementation/bot-02/`

This profile is an identity and boundary record, not a replacement for the
BOT-02 Blueprint, Implementation Contract, README, or Completion Record.

## Status

BOT-02 implementation is completed according to its recorded completion
boundary.

Future changes must not silently expand BOT-02 beyond its approved
architectural responsibility.
