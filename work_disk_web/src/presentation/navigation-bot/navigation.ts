export const NAVIGATION_ITEMS = [
  { id: 'dashboard', to: '/workspace/dashboard', label: 'Dashboard' },
  { id: 'finance', to: '/workspace/finance', label: 'Finance' },
  { id: 'history', to: '/workspace/history', label: 'History' },
  { id: 'settings', to: '/workspace/settings', label: 'Settings' },
] as const

export type NavigationSurface = 'dashboard' | 'social' | 'feed'

export function shouldShowNavigation(surface: NavigationSurface): boolean {
  return surface === 'dashboard'
}
