import { describe, expect, it } from 'vitest'
import { NAVIGATION_ITEMS, shouldShowNavigation } from './navigation'

describe('Navigation Buttons Bot', () => {
  it('owns exactly the five contracted workspace destinations', () => {
    expect(NAVIGATION_ITEMS.map((item) => item.id)).toEqual([
      'dashboard',
      'finance',
      'history',
      'settings',
      'profile',
    ])
  })

  it('shows workspace navigation only on the dashboard surface', () => {
    expect(shouldShowNavigation('dashboard')).toBe(true)
    expect(shouldShowNavigation('social')).toBe(false)
    expect(shouldShowNavigation('feed')).toBe(false)
  })
})
