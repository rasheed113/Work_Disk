# Work_Disk Web — BOT-04 Profile

## Identity

**Bot:** BOT-04  
**Name:** Delete Bot  
**Path:** `tools/lifecycle/delete`  
**Domain:** Lifecycle / Deletion  
**Role:** Authorised deletion lifecycle and execution boundary

## Governing Principle

> **Normal action executes normally. Approval-required action is held by Delete Bot until an authoritative approval decision commits or releases it.**

## Primary Responsibility

BOT-04 executes authorised deletion and owns the lifecycle of deletion operations that require approval.

It supports:

- immediate authorised deletion
- approval-gated deletion
- pending hold
- approval commit
- rejection release
- authoritative execution-result mapping

## Approval Model

BOT-04 does not decide whether approval is required or who approves.

The applicable authority/policy supplies the execution mode. The Warning & Approval Bot supplies the approval decision and evidence.

BOT-04 owns the pending deletion operation and does not require a separate Freeze Bot for this lifecycle.

## Hold Semantics

A held deletion means:

> deletion requested, target still exists, destructive execution not yet performed.

Rejection releases the hold. It does not restore a deleted target because no deletion occurred while the operation was held.

## Authority Model

BOT-04 does not create or grant domain authority.

It consumes authoritative authority context and, for approval-gated operations, authoritative approval evidence bound to the same request.

## Non-Responsibilities

BOT-04 is not responsible for:

- approval policy
- approver selection
- warning creation
- notification delivery
- account or identity authority
- Fleet/Contractor authority
- ownership decisions
- permission systems
- Mark/Mark All
- archive
- trash
- restore
- UI behaviour
- universal cleanup orchestration

## Verification Surface

Verification must cover:

- normal execution
- approval hold
- pending decision
- approval commit
- rejection release
- duplicate pending request protection
- approval evidence requirements
- execution failure after approval
- authority boundaries

## Repository State

This profile describes the approval-gated extension of the existing BOT-04 Delete Bot implementation.

## Boundary Rule

If future implementation requires an architectural decision not defined by the approved Blueprint or Implementation Contract:

> STOP — do not guess.
