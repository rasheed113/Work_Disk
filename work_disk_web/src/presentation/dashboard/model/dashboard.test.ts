import { describe, expect, it } from 'vitest'
import { DASHBOARD_CARD_DEFINITIONS, DEFAULT_DASHBOARD_ORDER, createDefaultDashboardPreferences } from './dashboard'

describe('Dashboard registry', () => {
  it('contains exactly the locked twelve core boundaries', () => {
    expect(DASHBOARD_CARD_DEFINITIONS).toHaveLength(12)
    expect(new Set(DASHBOARD_CARD_DEFINITIONS.map((card) => card.id)).size).toBe(12)
  })

  it('creates a non-destructive default preference state', () => {
    const preferences = createDefaultDashboardPreferences()
    expect(preferences.hidden).toEqual([])
    expect(preferences.pinned).toEqual([])
    expect(preferences.order).toEqual(DEFAULT_DASHBOARD_ORDER)
  })

  it('does not expose delete as a Dashboard card operation', () => {
    expect(DASHBOARD_CARD_DEFINITIONS.every((card) => 'removable' in card)).toBe(true)
    expect(DASHBOARD_CARD_DEFINITIONS.some((card) => card.title === 'Delete')).toBe(false)
  })
})
