import { useEffect, useState } from 'react'
import type { DashboardCardId, DashboardGridColumns, DashboardPreferences, DashboardViewMode } from '../model/dashboard'
import { createDefaultDashboardPreferences, DASHBOARD_CARD_DEFINITIONS, DEFAULT_DASHBOARD_ORDER } from '../model/dashboard'

const STORAGE_KEY = 'work-disk.dashboard.preferences.v1'
const REGISTRY_IDS = new Set(DASHBOARD_CARD_DEFINITIONS.map((definition) => definition.id))
const CONTENT_DEFINITIONS = DASHBOARD_CARD_DEFINITIONS.filter((definition) => definition.contentSurface)
const CONTENT_IDS = new Set(CONTENT_DEFINITIONS.map((definition) => definition.id))
const REGISTRY_ONLY_IDS = DEFAULT_DASHBOARD_ORDER.filter((id) => !CONTENT_IDS.has(id))

function isRegistryCardId(value: unknown): value is DashboardCardId {
  return typeof value === 'string' && REGISTRY_IDS.has(value as DashboardCardId)
}

function isContentCardId(value: unknown): value is DashboardCardId {
  return typeof value === 'string' && CONTENT_IDS.has(value as DashboardCardId)
}

function isViewMode(value: unknown): value is DashboardViewMode {
  return value === 'grid' || value === 'list'
}

function isGridColumns(value: unknown): value is DashboardGridColumns {
  return value === 2 || value === 3 || value === 4
}

export function normalizeDashboardOrder(value: unknown): DashboardCardId[] {
  // Persisted order is a presentation preference for the eight content surfaces.
  // The twelve-boundary registry remains authoritative, but registry-only boundaries
  // are kept in one canonical tail position so they can never appear as content or
  // become reorderable Dashboard cards.
  const contentOrder: DashboardCardId[] = []

  if (Array.isArray(value)) {
    for (const item of value) {
      if (isRegistryCardId(item) && isContentCardId(item) && !contentOrder.includes(item)) {
        contentOrder.push(item)
      }
    }
  }

  for (const definition of CONTENT_DEFINITIONS) {
    if (!contentOrder.includes(definition.id)) contentOrder.push(definition.id)
  }

  return [...contentOrder, ...REGISTRY_ONLY_IDS]
}

function readPreferences(): DashboardPreferences {
  try {
    const raw = window.localStorage.getItem(STORAGE_KEY)
    if (!raw) return createDefaultDashboardPreferences()
    const parsed = JSON.parse(raw) as Partial<DashboardPreferences>
    const base = createDefaultDashboardPreferences()
    return {
      hidden: Array.isArray(parsed.hidden) ? parsed.hidden.filter(isContentCardId) : base.hidden,
      pinned: Array.isArray(parsed.pinned) ? parsed.pinned.filter(isContentCardId) : base.pinned,
      order: normalizeDashboardOrder(parsed.order),
      viewMode: isViewMode(parsed.viewMode) ? parsed.viewMode : base.viewMode,
      gridColumns: isGridColumns(parsed.gridColumns) ? parsed.gridColumns : base.gridColumns,
    }
  } catch {
    return createDefaultDashboardPreferences()
  }
}

export function useDashboardPreferences() {
  const [preferences, setPreferences] = useState<DashboardPreferences>(readPreferences)

  useEffect(() => {
    window.localStorage.setItem(STORAGE_KEY, JSON.stringify(preferences))
  }, [preferences])

  const hide = (id: DashboardCardId) => setPreferences((current) => ({ ...current, hidden: [...new Set([...current.hidden, id])] }))
  const unhide = (id: DashboardCardId) => setPreferences((current) => ({ ...current, hidden: current.hidden.filter((item) => item !== id) }))
  const togglePin = (id: DashboardCardId) => setPreferences((current) => ({
    ...current,
    pinned: current.pinned.includes(id) ? current.pinned.filter((item) => item !== id) : [...current.pinned, id],
  }))
  const reorder = (id: DashboardCardId, direction: -1 | 1) => setPreferences((current) => {
    const contentOrder = current.order.filter((item) => CONTENT_IDS.has(item))
    const registryOnlyOrder = REGISTRY_ONLY_IDS
    const index = contentOrder.indexOf(id)
    const target = index + direction
    if (index < 0 || target < 0 || target >= contentOrder.length) return current
    ;[contentOrder[index], contentOrder[target]] = [contentOrder[target], contentOrder[index]]
    return { ...current, order: [...contentOrder, ...registryOnlyOrder] }
  })
  const setViewMode = (viewMode: DashboardViewMode) => setPreferences((current) => ({ ...current, viewMode }))
  const setGridColumns = (gridColumns: DashboardGridColumns) => setPreferences((current) => ({ ...current, gridColumns }))
  const reset = () => setPreferences(createDefaultDashboardPreferences())

  return { preferences, hide, unhide, togglePin, reorder, setViewMode, setGridColumns, reset }
}
