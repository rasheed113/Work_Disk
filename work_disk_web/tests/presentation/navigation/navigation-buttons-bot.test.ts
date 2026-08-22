import { describe, expect, it } from 'vitest'
import { NavigationButtonsBot } from '../../../src/presentation/navigation/navigation-buttons-bot'

describe('NavigationButtonsBot', () => {
  it('provides reusable core navigation intents', () => {
    const buttons = new NavigationButtonsBot().getButtons({
      registeredDestinations: new Set(['/dashboard']),
      availableCapabilities: new Set(),
    })

    expect(buttons.map((button) => button.kind)).toEqual([
      'BACK',
      'MORE',
      'CLOSE',
      'FORWARD',
      'HOME',
    ])
  })

  it('only exposes registered page destinations', () => {
    const buttons = new NavigationButtonsBot().getButtons({
      registeredDestinations: new Set(['/dashboard', '/page-2']),
      availableCapabilities: new Set(),
    })

    expect(buttons.some((button) => button.destination === '/page-2')).toBe(true)
    expect(buttons.some((button) => button.destination === '/fake')).toBe(false)
  })
})
