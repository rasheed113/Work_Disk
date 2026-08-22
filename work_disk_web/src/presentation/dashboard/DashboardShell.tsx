import type { DashboardModel } from './model/dashboard'

const EMPTY_MODEL: DashboardModel = { profile: null, capabilities: [], activities: [], notifications: [], summary: [], statusStrip: [] }

export function DashboardShell({ model = EMPTY_MODEL }: { model?: DashboardModel }) {
  void model
  return <main className="wd-dashboard-shell" id="dashboard">
    <div className="wd-dashboard-pagebar">
      <h1>Dashboard</h1>
    </div>
  </main>
}
