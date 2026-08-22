import { describe, expect, it } from 'vitest'
import { DASHBOARD_CARD_DEFINITIONS, DEFAULT_DASHBOARD_ORDER } from './model/dashboard'

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
})
