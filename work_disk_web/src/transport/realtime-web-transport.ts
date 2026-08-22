export interface WebTransportRequest<TPayload> {
  readonly operation: string
  readonly payload: TPayload
  readonly correlationId: string
}

export type WebTransportResult<TData> =
  | { readonly kind: 'success'; readonly data: TData }
  | { readonly kind: 'empty' }
  | { readonly kind: 'failure'; readonly code: string }

/**
 * Shared Web transport boundary.
 *
 * This is deliberately provider-neutral. HTTP/WebSocket/WASM providers may
 * implement it later, but page components and presentation adapters must only
 * depend on this boundary. It has no domain/database authority.
 */
export interface RealtimeWebTransport {
  request<TPayload, TData>(
    request: WebTransportRequest<TPayload>,
  ): Promise<WebTransportResult<TData>>
}

/**
 * Explicitly unavailable provider. It prevents accidental fake data while the
 * authoritative runtime transport provider is not yet wired.
 */
export const unavailableRealtimeWebTransport: RealtimeWebTransport = {
  async request() {
    return { kind: 'failure', code: 'TRANSPORT_PROVIDER_UNAVAILABLE' }
  },
}
