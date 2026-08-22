import { useMemo } from 'react'
import { Activity } from './components/Activity'
import { Capabilities } from './components/Capabilities'
import { CardsGallery } from './components/CardsGallery'
import { Customisation } from './components/Customisation'
import { DashboardCard } from './components/DashboardCard'
import { Header } from './components/Header'
import { Navigation } from './components/Navigation'
import { Notifications } from './components/Notifications'
import { Profile } from './components/Profile'
import { QuickActions } from './components/QuickActions'
import { SmartClock } from './components/SmartClock'
import { Summary } from './components/Summary'
import { Ticker } from './components/Ticker'
import { DASHBOARD_CARD_DEFINITIONS, type DashboardCardId, type DashboardModel } from './model/dashboard'
import { useDashboardPreferences } from './state/preferences'

const EMPTY_MODEL: DashboardModel = { profile: null, capabilities: [], activities: [], notifications: [], summary: [] }

export function DashboardShell({ model = EMPTY_MODEL }: { model?: DashboardModel }) {
  const { preferences, hide, unhide, togglePin, reorder, setViewMode, reset } = useDashboardPreferences()
  const order = useMemo(() => preferences.order.filter((id, index, ids) => ids.indexOf(id) === index), [preferences.order])
  const isHidden = (id: DashboardCardId) => preferences.hidden.includes(id)
  const controls = (id: DashboardCardId) => ({ hidden: isHidden(id), pinned: preferences.pinned.includes(id), onHide: () => hide(id), onPin: () => togglePin(id), onMoveUp: () => reorder(id, -1), onMoveDown: () => reorder(id, 1) })

  return <main className="wd-dashboard-shell" id="dashboard">
    <Header profile={model.profile} />
    <Navigation />
    <div className="wd-dashboard-toolbar" aria-label="Dashboard view mode">
      <span className="wd-dashboard-toolbar__label">View</span>
      <div className="wd-dashboard-view-toggle" role="group" aria-label="Dashboard view mode">
        <button type="button" className={preferences.viewMode === 'grid' ? 'is-active' : ''} aria-pressed={preferences.viewMode === 'grid'} onClick={() => setViewMode('grid')}>Grid</button>
        <button type="button" className={preferences.viewMode === 'list' ? 'is-active' : ''} aria-pressed={preferences.viewMode === 'list'} onClick={() => setViewMode('list')}>List</button>
      </div>
    </div>
    <div className={`wd-dashboard-grid wd-dashboard-grid--${preferences.viewMode}`}>
      {order.map((id) => {
        const card = DASHBOARD_CARD_DEFINITIONS.find((item) => item.id === id)
        if (!card) return null
        const common = controls(id)
        switch (id) {
          case 'header': return null
          case 'profile': return <DashboardCard key={id} {...common} id={id} title={card.title}><Profile profile={model.profile} /></DashboardCard>
          case 'navigation': return null
          case 'smart-clock': return <DashboardCard key={id} {...common} id={id} title={card.title}><SmartClock /></DashboardCard>
          case 'ticker': return <DashboardCard key={id} {...common} id={id} title={card.title}><Ticker /></DashboardCard>
          case 'quick-actions': return <DashboardCard key={id} {...common} id={id} title={card.title}><QuickActions actions={[]} /></DashboardCard>
          case 'summary': return <DashboardCard key={id} {...common} id={id} title={card.title}><Summary metrics={model.summary} /></DashboardCard>
          case 'activity': return <DashboardCard key={id} {...common} id={id} title={card.title}><Activity items={model.activities} /></DashboardCard>
          case 'notifications': return <DashboardCard key={id} {...common} id={id} title={card.title}><Notifications items={model.notifications} /></DashboardCard>
          case 'capabilities': return <DashboardCard key={id} {...common} id={id} title={card.title}><Capabilities capabilities={model.capabilities} /></DashboardCard>
          case 'customisation': return <DashboardCard key={id} id={id} title={card.title}><Customisation definitions={DASHBOARD_CARD_DEFINITIONS} hidden={preferences.hidden} pinned={preferences.pinned} onHide={hide} onUnhide={unhide} onTogglePin={togglePin} onReset={reset} /></DashboardCard>
          case 'cards-gallery': return <DashboardCard key={id} id={id} title={card.title}><CardsGallery definitions={DASHBOARD_CARD_DEFINITIONS} hidden={preferences.hidden} onUnhide={unhide} /></DashboardCard>
        }
      })}
    </div>
  </main>
}
