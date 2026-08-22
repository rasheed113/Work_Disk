import { describe, expect, it } from 'vitest'
import { createDefaultDashboardPreferences, DASHBOARD_CARD_DEFINITIONS, DEFAULT_DASHBOARD_ORDER } from './model/dashboard'
import { normalizeDashboardOrder } from './state/preferences'

describe('Work_Disk visible interface contract', () => {
  it('keeps the locked twelve-boundary registry while exposing only six content surfaces', () => {
    expect(DASHBOARD_CARD_DEFINITIONS).toHaveLength(12)
    expect(DEFAULT_DASHBOARD_ORDER).toHaveLength(12)
    expect(new Set(DEFAULT_DASHBOARD_ORDER).size).toBe(12)
    expect(DASHBOARD_CARD_DEFINITIONS.filter((card) => card.contentSurface)).toHaveLength(6)
    expect(DASHBOARD_CARD_DEFINITIONS.filter((card) => !card.contentSurface).map((card) => card.id)).toEqual([
      'profile', 'smart-clock', 'header', 'navigation', 'custom-dashboard', 'cards-gallery',
    ])
  })

  it('keeps Profile and Smart Clock as context-only presentation boundaries', () => {
    const profile = DASHBOARD_CARD_DEFINITIONS.find((card) => card.id === 'profile')!
    const smartClock = DASHBOARD_CARD_DEFINITIONS.find((card) => card.id === 'smart-clock')!
    expect(profile.contentSurface).toBe(false)
    expect(profile.removable).toBe(false)
    expect(smartClock.contentSurface).toBe(false)
    expect(smartClock.removable).toBe(false)
  })

  it('does not expose registry-only boundaries as Dashboard content', () => {
    const registryOnly = DASHBOARD_CARD_DEFINITIONS.filter((card) => !card.contentSurface)
    expect(registryOnly.every((card) => card.removable === false)).toBe(true)
    expect(registryOnly.map((card) => card.title)).toEqual(['Profile', 'Smart Clock', 'Header', 'Navigation', 'Custom Dashboard', 'Cards Gallery'])
  })

  it('migrates unknown legacy identifiers while preserving the locked registry boundaries', () => {
    expect(normalizeDashboardOrder([
      'header', 'profile', 'navigation', 'smart-clock', 'customisation', 'ticker', 'cards-gallery', 'profile', 'unknown',
    ])).toEqual([...DEFAULT_DASHBOARD_ORDER])
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
