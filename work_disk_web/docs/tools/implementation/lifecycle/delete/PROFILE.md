# Work_Disk Web — BOT-04 Delete Bot Profile

## Identity

**Bot:** BOT-04
**Name:** Delete Bot
**Path:** `tools/lifecycle/delete`
**Domain:** Lifecycle / Deletion
**Role:** Authorised generic deletion execution boundary

## Governing Principle

> Authority decides. Delete Bot executes.

## Primary Responsibility

BOT-04 executes an authorised deletion operation through the approved
deletion execution boundary and reports the authoritative result.

## Authority Model

BOT-04 does not create, grant, validate, replace, or own domain authority.

Required authority is established upstream by the applicable domain or
authorisation boundary.

Fleet warning and Contractor approval are outside BOT-04 and belong to a
separate Fleet-specific logical board.

## Input Boundary

A deletion request contains the required request identity, target identity,
and authoritative authorisation reference.

BOT-04 does not accept caller-controlled deletion semantics or caller-
controlled cascade scope.

Generic deletion does not require Fleet-specific approval fields.

## Execution Boundary

The `DeleteExecutionBoundary` represents the authoritative deletion
execution contract.

BOT-04 delegates deletion execution to that boundary and does not invent
domain-specific deletion behaviour.

## Result Boundary

BOT-04 exposes explicit outcomes for:

- deleted
- already deleted
- not found
- execution failure

Execution failure can identify:

- persistence failure
- transaction failure
- boundary failure

A failed authoritative operation must never be reported as successful.

## Idempotency

Repeated authorised deletion requests must not cause repeated destructive
effects.

An already-authoritatively-deleted target may return the approved
already-deleted outcome.

## Non-Responsibilities

BOT-04 is not responsible for:

- account or identity authority
- fleet authority
- Contractor approval
- permission systems
- ownership decisions
- Fleet warnings
- archive
- trash
- restore
- filtering
- sorting
- UI behaviour
- presentation cleanup
- universal cleanup orchestration
- unrelated domain business logic

## Verification Surface

BOT-04 has unit and integration verification covering the public result
contract, execution boundary, failure mapping, and complete authorised
execution flow, including generic deletion without Fleet approval fields.

## Repository State

Original implementation commit:

`3bda5f7`

Commit message:

`Implement BOT-04 delete lifecycle tool`

Current feature branch refines BOT-04 as the generic Delete Bot and keeps
Fleet warning/approval in a separate future board.

## Boundary Rule

If future implementation requires an architectural decision not defined by
the approved Blueprint or Implementation Contract:

> STOP — do not guess.
