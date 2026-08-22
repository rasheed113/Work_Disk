# Navigation Buttons BOT Contract

## Status
DESIGNED / CONTRACT LOCKED

## Purpose
Provide reusable navigation-control definitions for every Web page without owning page business logic.

## Supported button kinds
- BACK
- PAGE
- MORE
- CLOSE
- FORWARD
- HOME
- MENU

## Boundary
Navigation Buttons BOT → Navigation Presentation Adapter → Page UI

The BOT provides button intent and stable identity. Route/page authority remains with the navigation registry/router. Page business logic remains outside this BOT.

## Rules
- Buttons are reusable across pages.
- PAGE buttons reference an authoritative registered destination; they never invent routes.
- BACK/FORWARD operate on navigation history owned by the navigation runtime.
- MORE exposes page capabilities supplied by the page property/capability layer; it does not invent actions.
- HOME references the authoritative home/dashboard destination.
- CLOSE expresses navigation dismissal intent only.
- No domain data, persistence, authentication, role decisions, or page business logic lives here.
- Unavailable destination/capability produces no fake button behaviour.

## Four-page navigation board
The initial board may expose four page destinations: Dashboard plus three registered empty page shells. Empty shells contain no fake domain content and may receive real BOT components later.
