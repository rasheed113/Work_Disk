import { useMemo } from 'react'
import { Outlet, useLocation, useNavigate } from 'react-router-dom'
import { Footer } from '../../footer/Footer'
import { getPageProperty } from '../../page-properties/page-property-registry'
import { NavigationButtonsBot } from '../../navigation/navigation-buttons-bot'
import { BottomNavigationBoard } from '../../navigation/bottom-navigation-board'
import '../../navigation/bottom-navigation-board.css'

const NAVIGATION_DESTINATIONS = new Set([
  '/dashboard',
  '/history',
  '/finance',
  '/settings',
])

export function WorkspaceShell() {
  const navigate = useNavigate()
  const location = useLocation()
  const navigationProperty = getPageProperty('navigation')
  const navigationButtons = useMemo(
    () =>
      navigationProperty?.availability === 'AVAILABLE'
        ? new NavigationButtonsBot().getButtons({
            registeredDestinations: NAVIGATION_DESTINATIONS,
            availableCapabilities: new Set(),
          })
        : [],
    [navigationProperty],
  )

  const currentDestination =
    location.pathname === '/workspace/history'
      ? '/history'
      : location.pathname === '/workspace/finance'
        ? '/finance'
        : location.pathname === '/workspace/settings'
          ? '/settings'
          : '/dashboard'

  return (
    <main className="wd-workspace-shell" style={{ background: '#e8f7e8' }}>
      <header className="wd-workspace-header" aria-label="Work_Disk workspace header">
        <div className="wd-workspace-brand">
          <span className="wd-workspace-brand__mark" aria-hidden="true">WD</span>
          <div className="wd-workspace-brand__copy">
            <span className="wd-workspace-brand__title">WORK_DISK</span>
            <span className="wd-workspace-brand__subtitle">WORKSPACE</span>
          </div>
        </div>
        <p className="wd-workspace-header__description">One stable identity boundary with feature surfaces assembled around it.</p>
      </header>

      <section className="wd-workspace-content" style={{ background: '#e8f7e8', margin: 0, paddingBottom: '72px' }}>
        <Outlet />
      </section>

      <Footer />

      {navigationButtons.length > 0 && (
        <BottomNavigationBoard
          buttons={navigationButtons}
          activeDestination={currentDestination}
          onNavigate={(destination) => navigate(destination)}
        />
      )}
    </main>
  )
}
