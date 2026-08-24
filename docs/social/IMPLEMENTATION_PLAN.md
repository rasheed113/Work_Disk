# Social Implementation Plan

**Gate:** Implementation

## Vertical slice 01

Build the smallest real Social Web slice:

`Authenticated identity → Social Home → Post creation → persistent post → Home read → Like → Activity event`

## Boundaries

- `social/domain`: domain entities and invariants.
- `social/application`: use cases and ports.
- `social/infrastructure`: provider adapters, including Firebase when selected.
- `social/presentation`: web pages/components and page-owned properties.
- `social/tests`: unit/integration/security verification.

## Page ownership

- Home owns feed presentation and feed-specific controls.
- Post owns post creation UI and draft/publish state.
- Video owns video creation/playback entry.
- Profile owns social profile presentation.
- Inbox owns conversations and messages.
- Activity owns activity presentation.

## Provider rule

Firebase SDKs may appear only in infrastructure adapters. React pages and domain/application code must not import Firebase SDKs directly.

## No fake slice

The first slice must persist real records and read them back through the application boundary. Empty state is valid; fabricated posts are not.
