export type PagePropertyAvailability = 'AVAILABLE' | 'HIDDEN' | 'UNAVAILABLE'

export type PagePropertyId =
  | 'search'
  | 'filter'
  | 'sort'
  | 'selection'
  | 'actions'
  | 'edit'
  | 'delete'
  | 'share'
  | 'save'
  | 'notifications'
  | 'media'
  | 'more'
  | 'navigation'

export interface PagePropertyDefinition {
  readonly id: PagePropertyId
  readonly bot: string
  readonly availability: PagePropertyAvailability
}

/**
 * Presentation-only registry. It maps reusable page properties to existing
 * Tool-Bot identities; it does not execute domain logic or invent data.
 */
export const PAGE_PROPERTIES: readonly PagePropertyDefinition[] = [
  { id: 'search', bot: 'Search Tool-Bot', availability: 'AVAILABLE' },
  { id: 'filter', bot: 'Filter Tool-Bot', availability: 'AVAILABLE' },
  { id: 'sort', bot: 'Sort Tool-Bot', availability: 'AVAILABLE' },
  { id: 'selection', bot: 'Mark/Unmark Tool-Bot', availability: 'AVAILABLE' },
  { id: 'actions', bot: 'Action Board', availability: 'AVAILABLE' },
  { id: 'edit', bot: 'Edit Tool-Bot', availability: 'AVAILABLE' },
  { id: 'delete', bot: 'Delete Tool-Bot', availability: 'AVAILABLE' },
  { id: 'share', bot: 'Share/Repost capability', availability: 'AVAILABLE' },
  { id: 'save', bot: 'Save/Bookmark capability', availability: 'AVAILABLE' },
  { id: 'notifications', bot: 'Notification Tool-Bot', availability: 'AVAILABLE' },
  { id: 'media', bot: 'Media access/acquisition capability', availability: 'AVAILABLE' },
  { id: 'more', bot: 'Capability Registry', availability: 'AVAILABLE' },
  { id: 'navigation', bot: 'Navigation Buttons BOT', availability: 'AVAILABLE' },
] as const

export function getPageProperty(id: PagePropertyId): PagePropertyDefinition | undefined {
  return PAGE_PROPERTIES.find((property) => property.id === id)
}

export function visiblePageProperties(
  properties: readonly PagePropertyDefinition[] = PAGE_PROPERTIES,
): readonly PagePropertyDefinition[] {
  return properties.filter((property) => property.availability === 'AVAILABLE')
}
