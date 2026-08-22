import { describe, expect, it } from 'vitest'
import { AccountPresentationAdapter } from './AccountPresentationAdapter'

describe('AccountPresentationAdapter', () => {
  it('maps the authoritative BOT-01 account read model without inventing fields', () => {
    const adapter = new AccountPresentationAdapter()
    expect(adapter.toPresentation({ id: 'ACC123456', email: 'user@example.com' })).toEqual({
      id: 'ACC123456',
      email: 'user@example.com',
    })
  })
})
