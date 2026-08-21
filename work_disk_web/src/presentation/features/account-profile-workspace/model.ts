export interface AccountProfileModel {
  readonly accountId: string
  readonly displayName: string
  readonly profileCompletion?: number
}

export interface WorkspaceNavItem {
  readonly label: string
  readonly to: string
  readonly description: string
}

export const WORKSPACE_NAV_ITEMS: readonly WorkspaceNavItem[] = [
  { label: 'Dashboard', to: '/dashboard', description: 'Your configurable Work_Disk dashboard' },
  { label: 'Profile', to: '/profile', description: 'Account and profile context' },
  { label: 'Settings', to: '/settings', description: 'Preferences and configuration' },
]
