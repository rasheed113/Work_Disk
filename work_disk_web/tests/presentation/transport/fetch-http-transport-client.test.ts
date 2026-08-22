import { describe, expect, it, vi } from 'vitest'
import { FetchHttpTransportClient } from '../../../src/presentation/transport/fetch-http-transport-client'

describe('FetchHttpTransportClient', () => {
  const request = {
    requestId: 'req-account-1',
    operation: 'account.get',
    payload: { accountId: 'A123' },
  }

  it('maps an approved operation to its endpoint and preserves the wire request', async () => {
    const fetchImpl = vi.fn<typeof fetch>().mockResolvedValue(
      new Response(
        JSON.stringify({
          requestId: request.requestId,
          state: 'AUTHORITATIVE',
          payload: { id: 'A123', email: 'a@example.test' },
          error: null,
        }),
        { status: 200, headers: { 'Content-Type': 'application/json' } },
      ),
    )

    const client = new FetchHttpTransportClient({
      baseUrl: 'https://runtime.example',
      endpointForOperation: (operation) =>
        operation === 'account.get' ? '/api/v1/account/get' : undefined,
      fetchImpl,
    })

    await expect(client.request(request)).resolves.toMatchObject({
      state: 'AUTHORITATIVE',
      payload: { id: 'A123', email: 'a@example.test' },
    })

    expect(fetchImpl).toHaveBeenCalledWith(
      'https://runtime.example/api/v1/account/get',
      expect.objectContaining({
        method: 'POST',
        credentials: 'include',
        body: JSON.stringify(request),
      }),
    )
  })

  it('rejects an unrecognised operation instead of guessing an endpoint', async () => {
    const client = new FetchHttpTransportClient({
      endpointForOperation: () => undefined,
      fetchImpl: vi.fn<typeof fetch>(),
    })

    await expect(client.request(request)).rejects.toThrow(
      'WEB_TRANSPORT_OPERATION_UNRECOGNISED',
    )
  })

  it('rejects correlation mismatch from the runtime', async () => {
    const client = new FetchHttpTransportClient({
      endpointForOperation: () => '/api/v1/account/get',
      fetchImpl: vi.fn<typeof fetch>().mockResolvedValue(
        new Response(
          JSON.stringify({
            requestId: 'wrong-id',
            state: 'EMPTY',
            payload: null,
            error: null,
          }),
          { status: 200 },
        ),
      ),
    })

    await expect(client.request(request)).rejects.toThrow(
      'WEB_TRANSPORT_CORRELATION_MISMATCH',
    )
  })

  it('never converts malformed authoritative data into empty data', async () => {
    const client = new FetchHttpTransportClient({
      endpointForOperation: () => '/api/v1/account/get',
      fetchImpl: vi.fn<typeof fetch>().mockResolvedValue(
        new Response(
          JSON.stringify({
            requestId: request.requestId,
            state: 'AUTHORITATIVE',
            payload: null,
            error: null,
          }),
          { status: 200 },
        ),
      ),
    })

    await expect(client.request(request)).rejects.toThrow(
      'WEB_TRANSPORT_INVALID_AUTHORITATIVE_PAYLOAD',
    )
  })
})
