import { describe, expect, it } from 'vitest'
import { HttpWebTransportProvider } from '../../../src/presentation/transport/realtime-web-transport-provider-bot'

describe('HttpWebTransportProvider', () => {
  it('preserves an authoritative response and caller correlation', async () => {
    const provider = new HttpWebTransportProvider({
      async request(request) {
        expect(request.requestId).toBe('req-1')
        return {
          requestId: request.requestId,
          state: 'AUTHORITATIVE',
          payload: { profileId: 'P1' },
          error: null,
        }
      },
    })

    await expect(
      provider.request({
        operation: 'profile.assemble',
        payload: { profileId: 'P1' },
        correlationId: 'req-1',
      }),
    ).resolves.toEqual({
      state: 'AUTHORITATIVE',
      payload: { profileId: 'P1' },
    })
  })

  it('preserves an authoritative empty result', async () => {
    const provider = new HttpWebTransportProvider({
      async request(request) {
        return {
          requestId: request.requestId,
          state: 'EMPTY',
          payload: null,
          error: null,
        }
      },
    })

    await expect(
      provider.request({
        operation: 'profile.assemble',
        payload: { profileId: 'P2' },
        correlationId: 'req-2',
      }),
    ).resolves.toEqual({ state: 'EMPTY', payload: null })
  })

  it('rejects a correlation mismatch', async () => {
    const provider = new HttpWebTransportProvider({
      async request() {
        return {
          requestId: 'wrong-id',
          state: 'EMPTY',
          payload: null,
          error: null,
        }
      },
    })

    await expect(
      provider.request({
        operation: 'profile.assemble',
        payload: { profileId: 'P3' },
        correlationId: 'req-3',
      }),
    ).rejects.toThrow('WEB_TRANSPORT_CORRELATION_MISMATCH')
  })

  it('rejects an invalid authoritative envelope', async () => {
    const provider = new HttpWebTransportProvider({
      async request(request) {
        return {
          requestId: request.requestId,
          state: 'AUTHORITATIVE',
          payload: null,
          error: null,
        }
      },
    })

    await expect(
      provider.request({
        operation: 'profile.assemble',
        payload: { profileId: 'P4' },
        correlationId: 'req-4',
      }),
    ).rejects.toThrow('WEB_TRANSPORT_INVALID_AUTHORITATIVE_PAYLOAD')
  })

  it('does not convert provider/application errors into fake data', async () => {
    const provider = new HttpWebTransportProvider({
      async request(request) {
        return {
          requestId: request.requestId,
          state: 'ERROR',
          payload: null,
          error: { code: 'PROFILE_UNAVAILABLE', message: 'not available' },
        }
      },
    })

    await expect(
      provider.request({
        operation: 'profile.assemble',
        payload: { profileId: 'P5' },
        correlationId: 'req-5',
      }),
    ).rejects.toThrow('PROFILE_UNAVAILABLE')
  })
})
