import { describe, expect, it } from 'vitest'
import { BOTTOM_NAVIGATION_ITEMS } from '../../../src/presentation/navigation/bottom-navigation-board'

describe('BottomNavigationBoard', () => {
  it('defines exactly the four approved navigation destinations', () => {
    expect(BOTTOM_NAVIGATION_ITEMS).toEqual([
      { id: 'bottom-dashboard', label: 'Dashboard', destination: '/dashboard' },
      { id: 'bottom-history', label: 'History', destination: '/history' },
      { id: 'bottom-finance', label: 'Finance', destination: '/finance' },
      { id: 'bottom-settings', label: 'Settings', destination: '/settings' },
    ])
  })
})
