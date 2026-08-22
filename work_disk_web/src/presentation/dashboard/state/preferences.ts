import { useEffect, useState } from 'react'
import type { DashboardCardId, DashboardGridColumns, DashboardPreferences, DashboardViewMode } from '../model/dashboard'
import { createDefaultDashboardPreferences } from '../model/dashboard'

const STORAGE_KEY = 'work-disk.dashboard.preferences.v1'

function isCardId(value: unknown): value is DashboardCardId {
  return typeof value === 'string' && [
    'header', 'profile', 'navigation', 'smart-clock', 'ticker', 'quick-actions',
    'summary', 'activity', 'notifications', 'capabilities', 'customisation', 'cards-gallery',
  ].includes(value)
}

function isViewMode(value: unknown): value is DashboardViewMode {
  return value === 'grid' || value === 'list'
}

function isGridColumns(value: unknown): value is DashboardGridColumns {
  return value === 2 || value === 3 || value === 4
}

function readPreferences(): DashboardPreferences {
  try {
    const raw = window.localStorage.getItem(STORAGE_KEY)
    if (!raw) return createDefaultDashboardPreferences()
    const parsed = JSON.parse(raw) as Partial<DashboardPreferences>
    const base = createDefaultDashboardPreferences()
    return {
      hidden: Array.isArray(parsed.hidden) ? parsed.hidden.filter(isCardId) : base.hidden,
      pinned: Array.isArray(parsed.pinned) ? parsed.pinned.filter(isCardId) : base.pinned,
      order: Array.isArray(parsed.order) ? parsed.order.filter(isCardId) : base.order,
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
    const order = [...current.order]
    const index = order.indexOf(id)
    const target = index + direction
    if (index < 0 || target < 0 || target >= order.length) return current
    ;[order[index], order[target]] = [order[target], order[index]]
    return { ...current, order }
  })
  const setViewMode = (viewMode: DashboardViewMode) => setPreferences((current) => ({ ...current, viewMode }))
  const setGridColumns = (gridColumns: DashboardGridColumns) => setPreferences((current) => ({ ...current, gridColumns }))
  const reset = () => setPreferences(createDefaultDashboardPreferences())

  return { preferences, hide, unhide, togglePin, reorder, setViewMode, setGridColumns, reset }
}
