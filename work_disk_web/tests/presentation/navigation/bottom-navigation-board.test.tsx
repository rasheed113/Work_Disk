import { describe, expect, it } from 'vitest'
import { BottomNavigationBoard } from '../../../src/presentation/navigation/bottom-navigation-board'

describe('BottomNavigationBoard', () => {
  it('defines exactly the four approved navigation destinations', () => {
    const source = BottomNavigationBoard.toString()

    expect(source).toContain("label: 'Dashboard'")
    expect(source).toContain("label: 'History'")
    expect(source).toContain("label: 'Finance'")
    expect(source).toContain("label: 'Settings'")
    expect(source).toContain("destination: '/dashboard'")
    expect(source).toContain("destination: '/history'")
    expect(source).toContain("destination: '/finance'")
    expect(source).toContain("destination: '/settings'")
  })
})
