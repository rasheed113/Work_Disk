# Work_Disk Web — BOT-05 Evidence Verification Bot

BOT-05 is the evidence verification boundary for Work_Disk.

Its central rule is:

> Evidence can prove an existing authoritative transition; evidence cannot create one.

## What it verifies

BOT-05 checks:

- signature validity;
- signer eligibility at issuance;
- canonical lineage membership;
- domain/subject/resource/context binding;
- declared purpose;
- declared coverage;
- optional current-authority freshness;
- optional single-use consumption.

## What it does not do

BOT-05 does not:

- execute mutations;
- grant or revoke authority;
- choose consensus winners;
- mint evidence signatures;
- treat relay/gossip popularity as authority;
- turn historical evidence into current authority without an explicit request;
- delete non-canonical evidence.

## Verification model

`Evidence → Signature → Signer Eligibility → Context → Purpose → Coverage → Canonical Lineage → Optional Freshness → Optional Consumption`

The canonical state dependency is read-only from BOT-05's perspective.

## Important production boundary

The repository contains interfaces for cryptographic and authoritative-state
systems. It intentionally does not ship a pretend cryptographic algorithm.
Production integration must inject real implementations.

## Build the reference tests

From the repository root, compile the BOT-05 sources with C++17 and strict
warnings together with the unit/integration test source files. The test files
are standalone executables and use standard-library assertions only.

## Status

Architecture, implementation structure, verification tests, roadmap, and
completion record are maintained together under the BOT-05 boundary.
