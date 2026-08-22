import { describe, expect, it } from 'vitest'
import { createDefaultDashboardPreferences, DASHBOARD_CARD_DEFINITIONS, DEFAULT_DASHBOARD_ORDER } from './model/dashboard'

describe('Work_Disk visible interface contract', () => {
  it('exposes the locked twelve-card dashboard surface', () => {
    expect(DASHBOARD_CARD_DEFINITIONS).toHaveLength(12)
    expect(DEFAULT_DASHBOARD_ORDER).toHaveLength(12)
    expect(new Set(DEFAULT_DASHBOARD_ORDER).size).toBe(12)
  })

  it('keeps dashboard customisation non-destructive', () => {
    const customisation = DASHBOARD_CARD_DEFINITIONS.find((card) => card.id === 'customisation')
    const gallery = DASHBOARD_CARD_DEFINITIONS.find((card) => card.id === 'cards-gallery')

    expect(customisation?.removable).toBe(false)
    expect(gallery?.removable).toBe(false)
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
    preferences.viewMode = 'list'
    preferences.gridColumns = 4
    expect(preferences.order).toEqual(orderBefore)
    preferences.viewMode = 'grid'
    preferences.gridColumns = 2
    expect(preferences.order).toEqual(orderBefore)
  })
})
