# Work_Disk Web — Dashboard Mobile Responsive UX Architecture

## Purpose

Define the presentation-only architecture required to make the Dashboard professional and safe across narrow mobile viewports without changing domain authority.

## Evidence

Visual inspection confirmed mobile horizontal overflow for 3/4-column selections, dense permanent card controls, repeated empty-state copy, and a crowded presentation toolbar.

## Architecture

`Dashboard Model → View Mode Presentation → Responsive Grid Policy → Card Surface → Optional Customize Mode`

Customize Mode is ephemeral UI state. It does not become domain state and does not access services, repositories, or persistence.

## Locked principles

- Grid/List remains presentation state.
- Grid defaults to two columns.
- Grid column preference remains exactly 2, 3, or 4.
- Mobile responsive policy may constrain the rendered density without changing the stored presentation preference.
- Mobile Grid remains a real Grid.
- Hide/Unhide remains non-destructive.
- Card order and pin state remain independent from presentation mode.
- Empty states remain authoritative and honest.
- No BOT-01/BOT-02 changes.
