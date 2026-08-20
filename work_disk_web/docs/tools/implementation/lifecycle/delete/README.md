# Work_Disk Web — BOT-04 Delete Bot

## Purpose

BOT-04 is the Work_Disk generic deletion execution tool.

Its responsibility is strictly limited to executing an authorised deletion
operation through the approved execution boundary.

The governing principle is:

> Authority decides. Delete Bot executes.

BOT-04 does not decide whether deletion is authorised.

## Boundary

BOT-04 receives a deletion request containing:

- request identifier
- target type
- target identifier
- authoritative authorisation reference

Authority and domain decisions remain outside BOT-04.

BOT-04 does not own:

- account authority
- identity authority
- fleet authority
- contractor approval
- ownership decisions
- permission decisions
- archive behaviour
- trash behaviour
- restore behaviour
- filtering
- sorting
- UI behaviour
- universal cleanup
- unrelated domain operations

Fleet warning/approval is intentionally separated into a future
Fleet-specific logical board. That board may establish the required
upstream authority and then invoke BOT-04. BOT-04 itself contains no
Fleet approval workflow.

## Deletion Execution

The deletion request crosses the `DeleteExecutionBoundary`.

The authoritative boundary is responsible for target validation and
authoritative deletion according to the applicable domain contract.

BOT-04 reports the authoritative execution result.

Caller-controlled deletion semantics and caller-controlled cascade scope are
not supported.

## Result Contract

BOT-04 exposes explicit deletion outcomes:

- `Deleted`
- `AlreadyDeleted`
- `NotFound`
- `ExecutionFailed`

Execution failures distinguish relevant failure categories including:

- persistence failure
- transaction failure
- boundary failure

Successful deletion is reported only from an authoritative successful result.

`AlreadyDeleted` is treated as a successful idempotent outcome.

## Safety

BOT-04 must not:

- grant authority
- bypass authority
- invent deletion semantics
- expand deletion scope
- convert execution failure into success
- interpret presentation expiry as deletion
- silently destroy protected historical or evidence data
- implement Fleet approval semantics

Undefined destructive behaviour remains a STOP condition.

## Implementation

The implementation consists of:

- `delete_request.h`
- `delete_error.h`
- `delete_result.h`
- `delete_result.cpp`
- `delete_execution_boundary.h`
- `delete_execution_boundary.cpp`
- `delete_tool.h`
- `delete_tool.cpp`

## Verification

BOT-04 verification includes:

- deletion result contract tests
- execution boundary contract tests
- execution boundary tests
- execution failure mapping tests
- complete integration boundary test
- generic deletion without Fleet-specific approval fields

The integration test verifies:

`authorised request → target validation → deletion execution → authoritative result`

## Status

BOT-04 generic Delete Bot implementation and boundary refinement are
complete on the feature branch. Fleet-specific warning/approval remains a
separate future board and is deliberately not part of BOT-04.

Original BOT-04 implementation commit:

`3bda5f7` — `Implement BOT-04 delete lifecycle tool`
