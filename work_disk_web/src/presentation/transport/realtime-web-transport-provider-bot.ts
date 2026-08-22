import type {
  WebTransportProvider,
  WebTransportRequest,
  WebTransportResponse,
} from './realtime-web-transport'

export interface TransportContext {
  readonly sessionToken?: string
  readonly accountId?: string
}

export interface ProviderRequest<TPayload> {
  readonly requestId: string
  readonly operation: string
  readonly payload: TPayload
  readonly context?: TransportContext
}

export interface ProviderError {
  readonly code: string
  readonly message: string
}

export interface ProviderEnvelope<TPayload> {
  readonly requestId: string
  readonly state: 'AUTHORITATIVE' | 'EMPTY' | 'ERROR'
  readonly payload: TPayload | null
  readonly error: ProviderError | null
}

export interface HttpTransportClient {
  request<TResponse>(
    request: WebTransportRequest<ProviderRequest<unknown>>,
  ): Promise<ProviderEnvelope<TResponse>>
}

/**
 * Shared runtime provider BOT.
 *
 * It owns only the HTTP transport boundary. Domain authority remains in the
 * operation's authoritative BOT/service and presentation remains downstream.
 */
export class HttpWebTransportProvider<TRequest, TResponse>
  implements WebTransportProvider<TRequest, TResponse>
{
  readonly state = 'READY' as const

  constructor(private readonly client: HttpTransportClient) {}

  async request(
    request: WebTransportRequest<TRequest>,
  ): Promise<WebTransportResponse<TResponse>> {
    const envelope = await this.client.request<TResponse>({
      operation: request.operation,
      payload: request.payload,
    })

    if (envelope.state === 'ERROR') {
      throw new Error(
        envelope.error?.code ?? 'WEB_TRANSPORT_APPLICATION_ERROR',
      )
    }

    return {
      state: envelope.state,
      payload: envelope.payload,
    }
  }
}
