# Action Board — Blueprint

## Responsibility

Discover which authorised actions are applicable to a current selection and context, then return declarative action descriptors.

## Flow

`BOT-09 selection -> Action Board -> applicable action descriptors -> selected action tool`

The Action Board does not execute Delete, Move, Archive, Download, Export, or any future action.

## Inputs

- request identity
- authority reference
- opaque context type/reference
- BOT-09 selection reference/count or all-in-scope marker

## Outputs

- result code
- zero or more action descriptors
- action id
- safe display label
- tool reference

## Separation

Selection is owned by BOT-09. Authority is supplied by the caller/domain. Actual execution and final authority/state validation belong to the individual action tool.
