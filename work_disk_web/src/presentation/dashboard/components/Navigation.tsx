import { NavLink } from 'react-router-dom'
import { NAVIGATION_ITEMS, shouldShowNavigation, type NavigationSurface } from '../../navigation-bot/navigation'

export function Navigation({ surface = 'dashboard' }: { surface?: NavigationSurface }) {
  if (!shouldShowNavigation(surface)) return null

  return (
    <nav className="wd-navigation-buttons" aria-label="Workspace feature navigation">
      <ul>
        {NAVIGATION_ITEMS.map((item) => (
          <li key={item.id}>
            <NavLink to={item.to}>{item.label}</NavLink>
          </li>
        ))}
      </ul>
    </nav>
  )
}
