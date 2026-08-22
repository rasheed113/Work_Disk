# Real-Time Web Transport — Architecture Attack

## Audit target

Determine whether Web pages can consume authoritative Work_Disk BOT/service results through an existing shared runtime transport without bypassing contracts.

## Findings

1. BOT/service authority exists independently of presentation.
2. Profile BOT-02 exposes `ProfileService::assemble(...)` as its authoritative assembly path.
3. The repository contains a Profile Presentation Adapter, but that adapter is intentionally transport-neutral.
4. No authoritative HTTP/WebSocket/WASM runtime provider was found in the current Web repository search.
5. Therefore the missing layer is a shared transport boundary/provider, not another Profile domain implementation and not another Dashboard shortcut.

## Decision

Establish one provider-neutral shared Web transport boundary. Pages consume its results through their own presentation adapters.

## Rejected shortcuts

- Direct Dashboard → BOT/service calls.
- Direct Dashboard → repository/database calls.
- One transport implementation per page.
- Fake profile payloads while transport is unavailable.
- Hardcoded REST/WebSocket URLs without an authoritative protocol contract.

## Gate

The provider-neutral boundary may be implemented and tested now. A concrete runtime provider is blocked until the authoritative protocol/runtime integration is defined and available.
