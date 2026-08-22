import { useMemo, useState } from 'react'
import { Activity } from './components/Activity'
import { Capabilities } from './components/Capabilities'
import { Customisation } from './components/Customisation'
import { DashboardCard } from './components/DashboardCard'
import { Header } from './components/Header'
import { Notifications } from './components/Notifications'
import { Profile } from './components/Profile'
import { QuickActions } from './components/QuickActions'
import { SmartClock } from './components/SmartClock'
import { Summary } from './components/Summary'
import { Ticker } from './components/Ticker'
import { DASHBOARD_CARD_DEFINITIONS, type DashboardGridColumns, type DashboardModel } from './model/dashboard'
import { useDashboardPreferences } from './state/preferences'
import { Navigation } from './components/Navigation'

const EMPTY_MODEL: DashboardModel = { profile: null, capabilities: [], activities: [], notifications: [], summary: [] }
const GRID_COLUMNS: readonly DashboardGridColumns[] = [2, 3, 4]

export function DashboardShell({ model = EMPTY_MODEL }: { model?: DashboardModel }) {
  const { preferences, hide, unhide, togglePin, reorder, setViewMode, setGridColumns, reset } = useDashboardPreferences()
  const [isCustomizing, setIsCustomizing] = useState(false)
  const [isMoreOpen, setIsMoreOpen] = useState(false)
  const order = useMemo(() => [...preferences.order], [preferences.order])
  const contentIds = useMemo(() => new Set(DASHBOARD_CARD_DEFINITIONS.filter((definition) => definition.contentSurface).map((definition) => definition.id)), [])
  const visibleOrder = useMemo(() => order.filter((id) => contentIds.has(id) && !preferences.hidden.includes(id)), [order, preferences.hidden, contentIds])
  const customisationOrder = useMemo(() => order.filter((id) => contentIds.has(id)), [order, contentIds])

  return <main className="wd-dashboard-shell" id="dashboard">
    <Header profile={model.profile} />
    <div className="wd-dashboard-pagebar">
      <h1>Dashboard</h1>
      <div className="wd-dashboard-more">
        <button type="button" className="wd-dashboard-more__toggle" aria-expanded={isMoreOpen} aria-haspopup="menu" onClick={() => setIsMoreOpen((current) => !current)}>More <span aria-hidden="true">▾</span></button>
        {isMoreOpen && <div className="wd-dashboard-more__menu" role="menu" aria-label="Dashboard options">
          <div className="wd-dashboard-more__section">View</div>
          <button type="button" role="menuitem" className={preferences.viewMode === 'grid' ? 'is-selected' : ''} onClick={() => { setViewMode('grid'); setIsMoreOpen(false) }}>Grid</button>
          <button type="button" role="menuitem" className={preferences.viewMode === 'list' ? 'is-selected' : ''} onClick={() => { setViewMode('list'); setIsMoreOpen(false) }}>List</button>
          {preferences.viewMode === 'grid' && <label className="wd-dashboard-more__columns"><span>Columns</span><select aria-label="Grid columns" value={preferences.gridColumns} onChange={(event) => setGridColumns(Number(event.target.value) as DashboardGridColumns)}>{GRID_COLUMNS.map((columns) => <option key={columns} value={columns}>{columns}</option>)}</select></label>}
          <button type="button" role="menuitem" onClick={() => { setIsCustomizing(true); setIsMoreOpen(false) }}>Customize Dashboard</button>
          <button type="button" role="menuitem" disabled aria-disabled="true">Filter</button>
          <button type="button" role="menuitem" disabled aria-disabled="true">Sort By</button>
          <button type="button" role="menuitem" disabled aria-disabled="true">Cards Gallery</button>
        </div>}
      </div>
    </div>
    <section className="wd-dashboard-profile-context" aria-label="Profile context">
      <div className="wd-dashboard-profile-context__identity">
        <div className="wd-dashboard-profile-context__cover" aria-hidden="true" />
        <div className="wd-dashboard-profile-context__details">
          <div className="wd-dashboard-profile-context__avatar" aria-hidden="true">{model.profile?.displayName?.slice(0, 1).toUpperCase() ?? 'P'}</div>
          <div><strong>{model.profile?.displayName ?? 'Profile'}</strong><span>{model.profile?.accountId ?? 'Account ID unavailable'}</span>{model.profile?.accountId && <button type="button" onClick={() => navigator.clipboard?.writeText(model.profile!.accountId)}>Copy ID</button>}</div>
        </div>
      </div>
      <div className="wd-dashboard-profile-context__clock"><SmartClock /></div>
    </section>
    <label className="wd-dashboard-search"><span aria-hidden="true">⌕</span><input type="search" placeholder="Search Dashboard..." aria-label="Search Dashboard" /></label>
    {isCustomizing && <Customisation
      definitions={DASHBOARD_CARD_DEFINITIONS}
      order={customisationOrder}
      hidden={preferences.hidden}
      pinned={preferences.pinned}
      onHide={hide}
      onUnhide={unhide}
      onTogglePin={togglePin}
      onMoveUp={(id) => reorder(id, -1)}
      onMoveDown={(id) => reorder(id, 1)}
      onReset={reset}
    />}
    <div className={`wd-dashboard-grid wd-dashboard-grid--${preferences.viewMode} wd-dashboard-grid--columns-${preferences.gridColumns}`}>
      {visibleOrder.map((id) => {
        const card = DASHBOARD_CARD_DEFINITIONS.find((item) => item.id === id)
        if (!card) return null
        switch (id) {
          case 'profile': return <DashboardCard key={id} id={id} title={card.title}><Profile profile={model.profile} /></DashboardCard>
          case 'smart-clock': return <DashboardCard key={id} id={id} title={card.title}><SmartClock /></DashboardCard>
          case 'ticker': return <DashboardCard key={id} id={id} title={card.title}><Ticker /></DashboardCard>
          case 'quick-actions': return <DashboardCard key={id} id={id} title={card.title}><QuickActions actions={[]} /></DashboardCard>
          case 'summary': return <DashboardCard key={id} id={id} title={card.title}><Summary metrics={model.summary} /></DashboardCard>
          case 'activity': return <DashboardCard key={id} id={id} title={card.title}><Activity items={model.activities} /></DashboardCard>
          case 'notifications': return <DashboardCard key={id} id={id} title={card.title}><Notifications items={model.notifications} /></DashboardCard>
          case 'capabilities': return <DashboardCard key={id} id={id} title={card.title}><Capabilities capabilities={model.capabilities} /></DashboardCard>
        }
      })}
    </div>
    <Navigation />
  </main>
}
