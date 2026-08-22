import { describe, expect, it } from 'vitest'
import { render, screen } from '@testing-library/react'
import { Footer } from './Footer'

describe('Footer presentation boundary', () => {
  it('renders the contracted stable footer identity', () => {
    render(<Footer />)
    expect(screen.getByRole('contentinfo', { name: 'Work_Disk footer' })).toBeTruthy()
    expect(screen.getByText('WORK_DISK')).toBeTruthy()
    expect(screen.getByText('Workspace')).toBeTruthy()
  })
})
