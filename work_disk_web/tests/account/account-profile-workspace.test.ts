import { describe, expect, it } from 'vitest'
import { WORKSPACE_NAV_ITEMS } from '../../src/presentation/features/account-profile-workspace/model'

describe('Account/Profile + Workspace feature surface', () => {
  it('registers only presentation navigation destinations', () => {
    expect(WORKSPACE_NAV_ITEMS.map((item) => item.to)).toEqual([
      '/dashboard',
      '/profile',
      '/settings',
    ])
  })

  it('does not assign permission semantics to navigation items', () => {
    expect(WORKSPACE_NAV_ITEMS.every((item) => !('permission' in item))).toBe(true)
  })

  it('keeps navigation labels unique', () => {
    const labels = WORKSPACE_NAV_ITEMS.map((item) => item.label)
    expect(new Set(labels).size).toBe(labels.length)
  })
})
