import type {
  TransportContext,
  WebTransportProvider,
  WebTransportRequest,
  WebTransportResponse,
} from './realtime-web-transport'

export type { TransportContext } from './realtime-web-transport'

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
  request<TPayload, TResponse>(
    request: ProviderRequest<TPayload>,
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
    const providerRequest: ProviderRequest<TRequest> = {
      requestId: request.correlationId,
      operation: request.operation,
      payload: request.payload,
      context: request.context,
    }

    const envelope = await this.client.request<TRequest, TResponse>(
      providerRequest,
    )

    if (envelope.requestId !== request.correlationId) {
      throw new Error('WEB_TRANSPORT_CORRELATION_MISMATCH')
    }

    if (envelope.state === 'ERROR') {
      throw new Error(
        envelope.error?.code ?? 'WEB_TRANSPORT_APPLICATION_ERROR',
      )
    }

    if (envelope.state === 'AUTHORITATIVE' && envelope.payload === null) {
      throw new Error('WEB_TRANSPORT_INVALID_AUTHORITATIVE_PAYLOAD')
    }

    if (envelope.state === 'EMPTY' && envelope.payload !== null) {
      throw new Error('WEB_TRANSPORT_INVALID_EMPTY_PAYLOAD')
    }

    return {
      state: envelope.state,
      payload: envelope.payload,
    }
  }
}
