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

  it('defaults the presentation view to Grid', () => {
    const preferences = createDefaultDashboardPreferences()
    expect(preferences.viewMode).toBe('grid')
  })

  it('treats Grid and List as presentation modes without changing the card order contract', () => {
    const preferences = createDefaultDashboardPreferences()
    const orderBefore = [...preferences.order]
    preferences.viewMode = 'list'
    expect(preferences.order).toEqual(orderBefore)
    preferences.viewMode = 'grid'
    expect(preferences.order).toEqual(orderBefore)
  })
})
