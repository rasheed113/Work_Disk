import { describe, expect, it } from 'vitest'
import { HttpWebTransportProvider } from '../../../src/presentation/transport/realtime-web-transport-provider-bot'

describe('HttpWebTransportProvider', () => {
  it('preserves an authoritative response', async () => {
    const provider = new HttpWebTransportProvider({
      async request() {
        return {
          requestId: 'req-1',
          state: 'AUTHORITATIVE',
          payload: { profileId: 'P1' },
          error: null,
        }
      },
    })

    await expect(
      provider.request({ operation: 'profile.assemble', payload: { profileId: 'P1' } }),
    ).resolves.toEqual({
      state: 'AUTHORITATIVE',
      payload: { profileId: 'P1' },
    })
  })

  it('preserves an authoritative empty result', async () => {
    const provider = new HttpWebTransportProvider({
      async request() {
        return {
          requestId: 'req-2',
          state: 'EMPTY',
          payload: null,
          error: null,
        }
      },
    })

    await expect(
      provider.request({ operation: 'profile.assemble', payload: { profileId: 'P2' } }),
    ).resolves.toEqual({ state: 'EMPTY', payload: null })
  })

  it('does not convert provider/application errors into fake data', async () => {
    const provider = new HttpWebTransportProvider({
      async request() {
        return {
          requestId: 'req-3',
          state: 'ERROR',
          payload: null,
          error: { code: 'PROFILE_UNAVAILABLE', message: 'not available' },
        }
      },
    })

    await expect(
      provider.request({ operation: 'profile.assemble', payload: { profileId: 'P3' } }),
    ).rejects.toThrow('PROFILE_UNAVAILABLE')
  })
})
