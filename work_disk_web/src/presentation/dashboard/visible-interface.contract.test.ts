import { describe, expect, it } from 'vitest'
import { createDefaultDashboardPreferences, DASHBOARD_CARD_DEFINITIONS, DEFAULT_DASHBOARD_ORDER } from './model/dashboard'
import { normalizeDashboardOrder } from './state/preferences'

describe('Work_Disk visible interface contract', () => {
  it('exposes only user-facing dashboard content cards', () => {
    expect(DASHBOARD_CARD_DEFINITIONS).toHaveLength(8)
    expect(DEFAULT_DASHBOARD_ORDER).toHaveLength(8)
    expect(new Set(DEFAULT_DASHBOARD_ORDER).size).toBe(8)
    expect(DASHBOARD_CARD_DEFINITIONS.every((card) => card.removable)).toBe(true)
  })

  it('does not model navigation, customization or card registry surfaces as dashboard cards', () => {
    const ids = new Set(DEFAULT_DASHBOARD_ORDER)
    expect(ids.has('profile')).toBe(true)
    expect(ids.has('smart-clock')).toBe(true)
    expect(ids.has('ticker')).toBe(true)
    expect(ids.has('quick-actions')).toBe(true)
    expect(ids.has('summary')).toBe(true)
    expect(ids.has('activity')).toBe(true)
    expect(ids.has('notifications')).toBe(true)
    expect(ids.has('capabilities')).toBe(true)
  })

  it('migrates legacy non-content card ids out of persisted order without losing valid content order', () => {
    expect(normalizeDashboardOrder([
      'header', 'profile', 'navigation', 'smart-clock', 'customisation', 'ticker', 'cards-gallery', 'profile', 'unknown',
    ])).toEqual(['profile', 'smart-clock', 'ticker', 'quick-actions', 'summary', 'activity', 'notifications', 'capabilities'])
  })

  it('defaults the presentation view to Grid with two columns', () => {
    const preferences = createDefaultDashboardPreferences()
    expect(preferences.viewMode).toBe('grid')
    expect(preferences.gridColumns).toBe(2)
  })

  it('supports only the contracted 2, 3 and 4 grid column choices', () => {
    const preferences = createDefaultDashboardPreferences()
    const choices = [2, 3, 4] as const
    expect(choices).toContain(preferences.gridColumns)
    for (const columns of choices) {
      preferences.gridColumns = columns
      expect(preferences.gridColumns).toBe(columns)
    }
  })

  it('treats Grid/List and column count as presentation preferences without changing card order', () => {
    const preferences = createDefaultDashboardPreferences()
    const orderBefore = [...preferences.order]
    const hiddenBefore = [...preferences.hidden]
    const pinnedBefore = [...preferences.pinned]

    preferences.viewMode = 'list'
    preferences.gridColumns = 4
    expect(preferences.order).toEqual(orderBefore)
    expect(preferences.hidden).toEqual(hiddenBefore)
    expect(preferences.pinned).toEqual(pinnedBefore)

    preferences.viewMode = 'grid'
    preferences.gridColumns = 2
    expect(preferences.order).toEqual(orderBefore)
    expect(preferences.hidden).toEqual(hiddenBefore)
    expect(preferences.pinned).toEqual(pinnedBefore)
  })

  it('keeps mobile density presentation-only', () => {
    const preferences = createDefaultDashboardPreferences()
    preferences.viewMode = 'grid'
    preferences.gridColumns = 4

    expect(preferences.viewMode).toBe('grid')
    expect(preferences.gridColumns).toBe(4)
    expect(preferences.order).toEqual(DEFAULT_DASHBOARD_ORDER)
  })
})
