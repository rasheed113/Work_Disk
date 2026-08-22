import { describe, expect, it } from 'vitest'
import { createUnavailableWebTransport } from './realtime-web-transport'

describe('shared Web transport boundary', () => {
  it('exposes an explicit unavailable state when no provider exists', () => {
    const transport = createUnavailableWebTransport<unknown, unknown>()
    expect(transport.state).toBe('UNAVAILABLE')
  })

  it('never fabricates a response when the provider is unavailable', async () => {
    const transport = createUnavailableWebTransport<unknown, unknown>()
    await expect(
      transport.request({
        operation: 'profile.read',
        payload: {},
        correlationId: 'req-unavailable-1',
      }),
    ).rejects.toThrow('WEB_TRANSPORT_PROVIDER_UNAVAILABLE')
  })
})
