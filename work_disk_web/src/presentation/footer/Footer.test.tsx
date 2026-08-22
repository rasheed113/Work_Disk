import { describe, expect, it } from 'vitest'
import { FOOTER_ITEMS } from './Footer'

describe('Footer presentation boundary', () => {
  it('owns exactly the contracted stable footer identity', () => {
    expect(FOOTER_ITEMS).toEqual([
      { id: 'work-disk', label: 'WORK_DISK' },
      { id: 'workspace', label: 'Workspace' },
    ])
  })
})
