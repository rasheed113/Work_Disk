# Real-Time Web Transport — Architecture

## Purpose

Provide one shared transport boundary between Work_Disk authoritative BOT/service contracts and the Web presentation runtime.

## Locked boundary

```text
Authoritative BOT / Service
        ↓
Real-Time Web Transport Boundary
        ↓
Authoritative transport snapshot/result
        ↓
Page-specific Presentation Adapter
        ↓
Page View Model
        ↓
UI
```

## Ownership

- BOT/service remains authoritative for domain state and business rules.
- The transport boundary owns protocol/session/connection concerns only.
- Page-specific presentation adapters own UI projection only.
- Dashboard/page components do not call repositories or domain services directly.

## Shared transport rule

There is one transport boundary for the Web runtime. Pages do not create independent domain transports. Multiple BOT capabilities may use the shared transport while retaining their own contracts and authoritative ownership.

## Non-goals

- No domain business logic.
- No database access.
- No fabricated fallback data.
- No invented BOT contracts.
- No page-specific business rules.

## Current implementation state

The transport boundary is established as a contract/code boundary. A concrete network/WASM transport provider is intentionally not claimed until an authoritative runtime protocol is selected and implemented.
