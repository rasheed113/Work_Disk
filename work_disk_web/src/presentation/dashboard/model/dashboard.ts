export type DashboardCardId =
  | 'profile'
  | 'smart-clock'
  | 'ticker'
  | 'quick-actions'
  | 'summary'
  | 'activity'
  | 'notifications'
  | 'capabilities'
  | 'header'
  | 'navigation'
  | 'custom-dashboard'
  | 'cards-gallery'

export type DashboardViewMode = 'grid' | 'list'
export type DashboardGridColumns = 2 | 3 | 4

export interface DashboardCardDefinition {
  id: DashboardCardId
  title: string
  description: string
  removable: boolean
  contentSurface: boolean
}

export interface DashboardPreferences {
  hidden: DashboardCardId[]
  pinned: DashboardCardId[]
  order: DashboardCardId[]
  viewMode: DashboardViewMode
  gridColumns: DashboardGridColumns
}

export interface DashboardProfile { displayName: string; accountId: string }
export interface DashboardCapability { id: string; title: string; description: string; available: boolean }
export interface DashboardActivityItem { id: string; title: string; timestamp: string }
export interface DashboardNotification { id: string; title: string; timestamp: string; read: boolean }
export interface DashboardSummaryMetric { id: string; label: string; value: string }

export interface DashboardModel {
  profile: DashboardProfile | null
  capabilities: DashboardCapability[]
  activities: DashboardActivityItem[]
  notifications: DashboardNotification[]
  summary: DashboardSummaryMetric[]
}

export const DASHBOARD_CARD_DEFINITIONS: readonly DashboardCardDefinition[] = [
  { id: 'profile', title: 'Profile', description: 'Current profile context is presented above the cards.', removable: false, contentSurface: false },
  { id: 'smart-clock', title: 'Smart Clock', description: 'Current local time is presented above the cards.', removable: false, contentSurface: false },
  { id: 'ticker', title: 'Ticker / Status', description: 'Current status information.', removable: true, contentSurface: true },
  { id: 'quick-actions', title: 'Quick Actions', description: 'Available actions.', removable: true, contentSurface: true },
  { id: 'summary', title: 'Summary / KPI', description: 'Authoritative summary metrics.', removable: true, contentSurface: true },
  { id: 'activity', title: 'Activity', description: 'Recent activity supplied by the domain.', removable: true, contentSurface: true },
  { id: 'notifications', title: 'Notifications', description: 'Notification preview supplied by the notification service.', removable: true, contentSurface: true },
  { id: 'capabilities', title: 'Capabilities', description: 'Eligible capabilities available in the current context.', removable: true, contentSurface: true },
  { id: 'header', title: 'Header', description: 'Account and context presentation.', removable: false, contentSurface: false },
  { id: 'navigation', title: 'Navigation', description: 'Primary Work_Disk navigation.', removable: false, contentSurface: false },
  { id: 'custom-dashboard', title: 'Custom Dashboard', description: 'Dashboard personalisation controls.', removable: false, contentSurface: false },
  { id: 'cards-gallery', title: 'Cards Gallery', description: 'Registered dashboard cards.', removable: false, contentSurface: false },
]

export const DASHBOARD_CONTENT_DEFINITIONS = DASHBOARD_CARD_DEFINITIONS.filter((definition) => definition.contentSurface)
export const DEFAULT_DASHBOARD_ORDER: readonly DashboardCardId[] = DASHBOARD_CARD_DEFINITIONS.map(({ id }) => id)

export function createDefaultDashboardPreferences(): DashboardPreferences {
  return { hidden: [], pinned: [], order: [...DEFAULT_DASHBOARD_ORDER], viewMode: 'grid', gridColumns: 2 }
}
