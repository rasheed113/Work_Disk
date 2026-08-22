export type WebTransportState =
  | 'READY'
  | 'UNAVAILABLE'

export interface WebTransportRequest<TRequest> {
  readonly operation: string
  readonly payload: TRequest
}

export interface WebTransportResponse<TResponse> {
  readonly state: 'AUTHORIATIVE' | 'EMPTY'
  readonly payload: TResponse | null
}

export interface WebTransportProvider<TRequest, TResponse> {
  readonly state: WebTransportState
  request(
    request: WebTransportRequest<TRequest>,
  ): Promise<WebTransportResponse<TResponse>>
}

/**
 * Shared Web transport boundary.
 *
 * The transport carries authoritative provider results but does not know BOT
 * business rules or page presentation models. No provider means an explicit
 * unavailable state; it is never converted into fabricated data.
 */
export function createUnavailableWebTransport<
  TRequest,
  TResponse,
>(): WebTransportProvider<TRequest, TResponse> {
  return {
    state: 'UNAVAILABLE',
    async request() {
      throw new Error('WEB_TRANSPORT_PROVIDER_UNAVAILABLE')
    },
  }
}
