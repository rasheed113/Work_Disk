import type { NavigationButton } from './navigation-buttons-bot'

export interface BottomNavigationItem {
  readonly id: string
  readonly label: string
  readonly destination: string
}

export const BOTTOM_NAVIGATION_ITEMS: readonly BottomNavigationItem[] = [
  { id: 'bottom-dashboard', label: 'Dashboard', destination: '/dashboard' },
  { id: 'bottom-history', label: 'History', destination: '/history' },
  { id: 'bottom-finance', label: 'Finance', destination: '/finance' },
  { id: 'bottom-settings', label: 'Settings', destination: '/settings' },
]

/** Independent bottom navigation presentation component; not a Dashboard property. */
export function BottomNavigationBoard({
  buttons,
  activeDestination,
  onNavigate,
}: {
  readonly buttons: readonly NavigationButton[]
  readonly activeDestination?: string
  readonly onNavigate: (destination: string) => void
}) {
  return (
    <nav aria-label="Primary navigation" className="bottom-navigation-board">
      {BOTTOM_NAVIGATION_ITEMS.map((item) => {
        const button = buttons.find(
          (candidate) => candidate.destination === item.destination,
        )

        if (!button) return null

        const active = activeDestination === item.destination

        return (
          <button
            key={item.id}
            type="button"
            aria-label={item.label}
            aria-current={active ? 'page' : undefined}
            className={active ? 'bottom-navigation-board__button bottom-navigation-board__button--active' : 'bottom-navigation-board__button'}
            onClick={() => onNavigate(item.destination)}
          >
            {item.label}
          </button>
        )
      })}
    </nav>
  )
}
