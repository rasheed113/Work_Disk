import { describe, expect, it, vi } from 'vitest'
import { render, screen } from '@testing-library/react'
import { BottomNavigationBoard } from '../../../src/presentation/navigation/bottom-navigation-board'

describe('BottomNavigationBoard', () => {
  it('renders exactly the four approved navigation labels', () => {
    render(
      <BottomNavigationBoard
        buttons={[
          { id: '1', kind: 'PAGE', label: 'Dashboard', destination: '/dashboard' },
          { id: '2', kind: 'PAGE', label: '/history', destination: '/history' },
          { id: '3', kind: 'PAGE', label: '/finance', destination: '/finance' },
          { id: '4', kind: 'PAGE', label: '/settings', destination: '/settings' },
        ]}
        onNavigate={vi.fn()}
      />,
    )

    expect(screen.getAllByRole('button')).toHaveLength(4)
    expect(screen.getByRole('button', { name: 'Dashboard' })).toBeTruthy()
    expect(screen.getByRole('button', { name: 'History' })).toBeTruthy()
    expect(screen.getByRole('button', { name: 'Finance' })).toBeTruthy()
    expect(screen.getByRole('button', { name: 'Settings' })).toBeTruthy()
  })
})
