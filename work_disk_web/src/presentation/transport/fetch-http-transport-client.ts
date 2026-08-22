import type {
  HttpTransportClient,
  ProviderEnvelope,
  ProviderRequest,
} from './realtime-web-transport-provider-bot'

export interface FetchHttpTransportClientOptions {
  readonly baseUrl?: string
  readonly endpointForOperation: (operation: string) => string | undefined
  readonly fetchImpl?: typeof fetch
  readonly credentials?: RequestCredentials
}

/**
 * Concrete browser HTTP transport client for the shared Web Transport BOT.
 *
 * This class performs transport adaptation only. It does not know Account,
 * Profile, or any other domain service. Operation-to-endpoint ownership is
 * supplied explicitly by the caller so unrecognised operations are rejected
 * rather than guessed.
 */
export class FetchHttpTransportClient implements HttpTransportClient {
  private readonly baseUrl: string
  private readonly endpointForOperation: FetchHttpTransportClientOptions['endpointForOperation']
  private readonly fetchImpl: typeof fetch
  private readonly credentials: RequestCredentials

  constructor(options: FetchHttpTransportClientOptions) {
    this.baseUrl = options.baseUrl ?? ''
    this.endpointForOperation = options.endpointForOperation
    this.fetchImpl = options.fetchImpl ?? fetch
    this.credentials = options.credentials ?? 'include'
  }

  async request<TPayload, TResponse>(
    request: ProviderRequest<TPayload>,
  ): Promise<ProviderEnvelope<TResponse>> {
    const endpoint = this.endpointForOperation(request.operation)

    if (!endpoint) {
      throw new Error('WEB_TRANSPORT_OPERATION_UNRECOGNISED')
    }

    let response: Response

    try {
      response = await this.fetchImpl(`${this.baseUrl}${endpoint}`, {
        method: 'POST',
        credentials: this.credentials,
        headers: {
          Accept: 'application/json',
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(request),
      })
    } catch {
      throw new Error('WEB_TRANSPORT_NETWORK_ERROR')
    }

    let envelope: ProviderEnvelope<TResponse>

    try {
      envelope = (await response.json()) as ProviderEnvelope<TResponse>
    } catch {
      throw new Error('WEB_TRANSPORT_INVALID_RESPONSE')
    }

    if (envelope.requestId !== request.requestId) {
      throw new Error('WEB_TRANSPORT_CORRELATION_MISMATCH')
    }

    if (envelope.state === 'AUTHORITATIVE' && envelope.payload === null) {
      throw new Error('WEB_TRANSPORT_INVALID_AUTHORITATIVE_PAYLOAD')
    }

    if (envelope.state === 'EMPTY' && envelope.payload !== null) {
      throw new Error('WEB_TRANSPORT_INVALID_EMPTY_PAYLOAD')
    }

    if (envelope.state === 'ERROR' && envelope.payload !== null) {
      throw new Error('WEB_TRANSPORT_INVALID_ERROR_PAYLOAD')
    }

    if (!response.ok && envelope.state !== 'ERROR') {
      throw new Error('WEB_TRANSPORT_HTTP_STATUS_ERROR')
    }

    return envelope
  }
}
