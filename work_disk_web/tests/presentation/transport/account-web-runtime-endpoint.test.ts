import { describe, expect, it } from 'vitest'
import { AccountWebRuntimeEndpoint } from '../../../src/presentation/transport/account-web-runtime-endpoint'

describe('AccountWebRuntimeEndpoint', () => {
  const request = {
    requestId: 'account-test-1',
    operation: 'account.get' as const,
    payload: { accountId: 'ACC123456' },
  }

  it('delegates to the authoritative Account read service and preserves correlation', async () => {
    const getAccount = async () => ({
      id: 'ACC123456',
      email: 'owner@example.test',
    })
    const endpoint = new AccountWebRuntimeEndpoint({ getAccount })

    await expect(endpoint.handle(request)).resolves.toEqual({
      requestId: 'account-test-1',
      state: 'AUTHORITATIVE',
      payload: { id: 'ACC123456', email: 'owner@example.test' },
      error: null,
    })
  })

  it('preserves truthful empty state', async () => {
    const endpoint = new AccountWebRuntimeEndpoint({
      getAccount: async () => null,
    })

    await expect(endpoint.handle(request)).resolves.toEqual({
      requestId: 'account-test-1',
      state: 'EMPTY',
      payload: null,
      error: null,
    })
  })

  it('rejects a missing Account ID at the transport boundary', async () => {
    const getAccount = async () => ({ id: 'never', email: 'never@example.test' })
    const endpoint = new AccountWebRuntimeEndpoint({ getAccount })

    await expect(
      endpoint.handle({
        ...request,
        payload: { accountId: '   ' },
      }),
    ).resolves.toMatchObject({
      state: 'ERROR',
      payload: null,
      error: { code: 'ACCOUNT_ID_REQUIRED' },
    })
  })

  it('rejects an unregistered operation without calling domain authority', async () => {
    let called = false
    const endpoint = new AccountWebRuntimeEndpoint({
      getAccount: async () => {
        called = true
        return null
      },
    })

    await expect(
      endpoint.handle({
        ...request,
        operation: 'account.unknown' as 'account.get',
      }),
    ).resolves.toMatchObject({
      state: 'ERROR',
      error: { code: 'ACCOUNT_OPERATION_UNRECOGNISED' },
    })
    expect(called).toBe(false)
  })

  it('does not fabricate data when the authoritative read fails', async () => {
    const endpoint = new AccountWebRuntimeEndpoint({
      getAccount: async () => {
        throw new Error('repository failure')
      },
    })

    await expect(endpoint.handle(request)).resolves.toMatchObject({
      state: 'ERROR',
      payload: null,
      error: { code: 'ACCOUNT_READ_FAILED' },
    })
  })
})
