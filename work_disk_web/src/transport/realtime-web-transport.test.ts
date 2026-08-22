import { describe, expect, it } from 'vitest'
import { unavailableRealtimeWebTransport } from './realtime-web-transport'

describe('RealtimeWebTransport boundary', () => {
  it('does not fabricate data when no provider is wired', async () => {
    await expect(
      unavailableRealtimeWebTransport.request({
        operation: 'profile.assemble',
        payload: { profileId: 'profile-1' },
        correlationId: 'test-1',
      }),
    ).resolves.toEqual({
      kind: 'failure',
      code: 'TRANSPORT_PROVIDER_UNAVAILABLE',
    })
  })
})
