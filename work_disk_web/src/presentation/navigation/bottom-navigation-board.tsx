import type { NavigationButton } from './navigation-buttons-bot'

export interface BottomNavigationItem {
  readonly id: string
  readonly label: string
  readonly destination: string
}

const ITEMS: readonly BottomNavigationItem[] = [
  { id: 'bottom-dashboard', label: 'Dashboard', destination: '/dashboard' },
  { id: 'bottom-history', label: 'History', destination: '/history' },
  { id: 'bottom-finance', label: 'Finance', destination: '/finance' },
  { id: 'bottom-settings', label: 'Settings', destination: '/settings' },
]

/**
 * Independent bottom navigation presentation component.
 * It is not a Dashboard property. It consumes navigation intents supplied by
 * the Navigation Buttons BOT and maps the four registered destinations to the
 * product's current labels.
 */
export function BottomNavigationBoard({
  buttons,
  onNavigate,
}: {
  readonly buttons: readonly NavigationButton[]
  readonly onNavigate: (destination: string) => void
}) {
  return (
    <nav aria-label="Primary navigation" className="bottom-navigation-board">
      {ITEMS.map((item) => {
        const button = buttons.find(
          (candidate) => candidate.destination === item.destination,
        )

        if (!button) return null

        return (
          <button
            key={item.id}
            type="button"
            aria-label={item.label}
            onClick={() => onNavigate(item.destination)}
          >
            {item.label}
          </button>
        )
      })}
    </nav>
  )
}
