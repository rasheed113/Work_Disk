import { describe, expect, it } from 'vitest'
import {
  PAGE_PROPERTIES,
  getPageProperty,
  visiblePageProperties,
} from '../../../src/presentation/page-properties/page-property-registry'

describe('page property registry', () => {
  it('contains only reusable presentation properties mapped to Tool-Bot capabilities', () => {
    expect(PAGE_PROPERTIES).toHaveLength(13)
    expect(getPageProperty('search')?.bot).toBe('Search Tool-Bot')
    expect(getPageProperty('delete')?.bot).toBe('Delete Tool-Bot')
    expect(getPageProperty('notifications')?.bot).toBe('Notification Tool-Bot')
    expect(getPageProperty('navigation')?.bot).toBe('Navigation Buttons BOT')
  })

  it('never exposes hidden or unavailable properties as visible', () => {
    const result = visiblePageProperties([
      { id: 'search', bot: 'Search Tool-Bot', availability: 'AVAILABLE' },
      { id: 'edit', bot: 'Edit Tool-Bot', availability: 'HIDDEN' },
      { id: 'delete', bot: 'Delete Tool-Bot', availability: 'UNAVAILABLE' },
    ])

    expect(result.map((property) => property.id)).toEqual(['search'])
  })
})
