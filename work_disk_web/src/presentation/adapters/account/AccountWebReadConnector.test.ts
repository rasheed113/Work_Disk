import { describe, expect, it } from 'vitest'
import { AccountWebReadConnector, ACCOUNT_READ_OPERATION } from './AccountWebReadConnector'

describe('AccountWebReadConnector', () => {
  it('requests account.get and maps only the authoritative payload', async () => {
    const calls: unknown[] = []
    const connector = new AccountWebReadConnector({
      state: 'READY',
      async request(request) {
        calls.push(request)
        return {
          state: 'AUTHORITATIVE',
          payload: { id: 'ACC123456', email: 'user@example.com' },
        }
      },
    })

    await expect(connector.read('ACC123456')).resolves.toEqual({
      id: 'ACC123456',
      email: 'user@example.com',
    })

    expect(calls).toEqual([
      {
        operation: ACCOUNT_READ_OPERATION,
        payload: { accountId: 'ACC123456' },
      },
    ])
  })

  it('preserves truthful empty state as null', async () => {
    const connector = new AccountWebReadConnector({
      state: 'READY',
      async request() {
        return { state: 'EMPTY', payload: null }
      },
    })

    await expect(connector.read('ACC123456')).resolves.toBeNull()
  })

  it('rejects an authoritative response without its payload', async () => {
    const connector = new AccountWebReadConnector({
      state: 'READY',
      async request() {
        return { state: 'AUTHORITATIVE', payload: null }
      },
    })

    await expect(connector.read('ACC123456')).rejects.toThrow(
      'ACCOUNT_AUTHORITATIVE_PAYLOAD_MISSING',
    )
  })
})
