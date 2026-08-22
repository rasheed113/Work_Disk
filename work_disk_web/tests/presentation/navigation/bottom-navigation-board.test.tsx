import { describe, expect, it } from 'vitest'
import { BOTTOM_NAVIGATION_ITEMS } from '../../../src/presentation/navigation/bottom-navigation-board'

describe('BottomNavigationBoard', () => {
  it('defines exactly the four approved navigation destinations and their icons', () => {
    expect(BOTTOM_NAVIGATION_ITEMS).toEqual([
      { id: 'bottom-dashboard', label: 'Dashboard', icon: '🖥️', destination: '/dashboard' },
      { id: 'bottom-history', label: 'History', icon: '⏲️', destination: '/history' },
      { id: 'bottom-finance', label: 'Finance', icon: '🪙', destination: '/finance' },
      { id: 'bottom-settings', label: 'Settings', icon: '🔧', destination: '/settings' },
    ])
  })
})
