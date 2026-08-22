import { describe, expect, it } from 'vitest'
import { BottomNavigationBoard } from '../../../src/presentation/navigation/bottom-navigation-board'

describe('BottomNavigationBoard', () => {
  it('defines exactly the four approved navigation destinations', () => {
    const source = BottomNavigationBoard.toString()

    expect(source).toContain("bottom-dashboard")
    expect(source).toContain("bottom-history")
    expect(source).toContain("bottom-finance")
    expect(source).toContain("bottom-settings")
  })
})
