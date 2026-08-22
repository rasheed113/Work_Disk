# Real-Time Web Transport — Boundary

## Allowed inputs

A transport request may carry only data required by the already-authorised BOT/service contract, including request identity, operation identifier, correlation information and transport metadata.

## Allowed outputs

The transport returns authoritative BOT/service results or an explicit transport failure. It must not manufacture domain values.

## Forbidden dependencies

The transport boundary must not depend on Dashboard components, page state, presentation adapters, UI components, or direct domain database access.

## Page integration

Each page that consumes BOT data uses its own presentation adapter after transport delivery:

`BOT/service → shared transport → page-specific adapter → page UI`

## Empty/unavailable semantics

An authoritative empty result remains empty. Transport failure remains a transport failure. Neither is converted into dummy content.

## Security boundary

Authentication, session authority, device trust and permission decisions remain owned by their authoritative contracts. The transport carries/propagates those decisions; it does not redefine them.
