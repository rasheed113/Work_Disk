import type { DashboardModel } from './model/dashboard'

const EMPTY_MODEL: DashboardModel = { profile: null, capabilities: [], activities: [], notifications: [], summary: [], statusStrip: [] }

export function DashboardShell({ model = EMPTY_MODEL }: { model?: DashboardModel }) {
  void model
  return <main className="wd-dashboard-shell" id="dashboard">
    <div className="wd-dashboard-pagebar">
      <h1 style={{ transform: 'perspective(220px) rotateX(8deg)', textShadow: '0 1px 0 #b8b8b8, 0 2px 0 #929292, 0 3px 0 #707070, 0 5px 8px rgba(0,0,0,.28)', letterSpacing: '0.02em' }}>Dashboard</h1>
    </div>
  </main>
}
