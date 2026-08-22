import type { DashboardModel } from './model/dashboard'

const EMPTY_MODEL: DashboardModel = { profile: null, capabilities: [], activities: [], notifications: [], summary: [], statusStrip: [] }

export function DashboardShell({ model = EMPTY_MODEL }: { model?: DashboardModel }) {
  void model
  return <main className="wd-dashboard-shell wd-page-destination" id="dashboard" style={{ background: '#e8f7e8', minHeight: '100%' }}>
    <div className="wd-dashboard-pagebar wd-page-destination__bar">
      <h1 className="wd-page-destination__title">Dashboard</h1>
    </div>
  </main>
}
