# Real-Time Web Transport — Contract

## Contract ID

`WEB-TRANSPORT-01`

## Responsibility

Expose authoritative BOT/service operations to the Web runtime through one shared transport boundary without taking domain ownership.

## Request contract

```ts
export interface WebTransportRequest<TPayload> {
  readonly operation: string
  readonly payload: TPayload
  readonly correlationId: string
}
```

`operation` MUST identify an already-defined authoritative BOT/service operation. `payload` MUST conform to that operation's contract. `correlationId` MUST be transport metadata and MUST NOT become domain data.

## Result contract

```ts
export type WebTransportResult<TData> =
  | { readonly kind: 'success'; readonly data: TData }
  | { readonly kind: 'empty' }
  | { readonly kind: 'failure'; readonly code: string }
```

## Invariants

1. No operation may be invented by the transport.
2. No domain data may be fabricated.
3. No direct repository/database access from the Web transport boundary.
4. Transport failure MUST remain distinguishable from an authoritative empty result.
5. Page-specific presentation adapters remain downstream of transport.
6. The transport boundary MUST be replaceable by an HTTP/WebSocket/WASM provider without changing BOT contracts or page adapters.

## Runtime provider status

The contract is established. A concrete provider remains a separate implementation phase because the repository currently contains no authoritative Web network/WASM endpoint to bind to.
