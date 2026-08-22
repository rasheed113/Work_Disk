export type WebTransportState =
  | 'READY'
  | 'UNAVAILABLE'

export interface WebTransportRequest<TRequest> {
  readonly operation: string
  readonly payload: TRequest
}

export interface WebTransportResponse<TResponse> {
  readonly state: 'AUTHORITATIVE' | 'EMPTY'
  readonly payload: TResponse | null
}

export interface WebTransportProvider<TRequest, TResponse> {
  readonly state: WebTransportState
  request(
    request: WebTransportRequest<TRequest>,
  ): Promise<WebTransportResponse<TResponse>>
}

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
