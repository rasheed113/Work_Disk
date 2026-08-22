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

const EMPTY_MODEL: DashboardModel = { profile: null, capabilities: [], activities: [], notifications: [], summary: [] }
const GRID_COLUMNS: readonly DashboardGridColumns[] = [2, 3, 4]

export function DashboardShell({ model = EMPTY_MODEL }: { model?: DashboardModel }) {
  const { preferences, hide, unhide, togglePin, reorder, setViewMode, setGridColumns, reset } = useDashboardPreferences()
  const [isCustomizing, setIsCustomizing] = useState(false)
  const order = useMemo(() => [...preferences.order], [preferences.order])
  const contentIds = useMemo(() => new Set(DASHBOARD_CARD_DEFINITIONS.filter((definition) => definition.contentSurface).map((definition) => definition.id)), [])
  const visibleOrder = useMemo(() => order.filter((id) => contentIds.has(id) && !preferences.hidden.includes(id)), [order, preferences.hidden, contentIds])
  const customisationOrder = useMemo(() => order.filter((id) => contentIds.has(id)), [order, contentIds])

  return <main className="wd-dashboard-shell" id="dashboard">
    <Header profile={model.profile} />
    <div className={`wd-dashboard-toolbar${isCustomizing ? ' is-customizing' : ''}`} aria-label="Dashboard presentation controls">
      <span className="wd-dashboard-toolbar__label">View</span>
      <div className="wd-dashboard-view-toggle" role="group" aria-label="Dashboard view mode">
        <button type="button" className={preferences.viewMode === 'grid' ? 'is-active' : ''} aria-pressed={preferences.viewMode === 'grid'} onClick={() => setViewMode('grid')}>Grid</button>
        <button type="button" className={preferences.viewMode === 'list' ? 'is-active' : ''} aria-pressed={preferences.viewMode === 'list'} onClick={() => setViewMode('list')}>List</button>
      </div>
      {preferences.viewMode === 'grid' && <label className="wd-dashboard-grid-columns">
        <span>Columns</span>
        <select aria-label="Grid columns" value={preferences.gridColumns} onChange={(event) => setGridColumns(Number(event.target.value) as DashboardGridColumns)}>
          {GRID_COLUMNS.map((columns) => <option key={columns} value={columns}>{columns}</option>)}
        </select>
      </label>}
      <button type="button" className="wd-dashboard-customize-toggle" aria-pressed={isCustomizing} onClick={() => setIsCustomizing((current) => !current)}>
        {isCustomizing ? 'Done' : 'Customize'}
      </button>
    </div>
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
  </main>
}
