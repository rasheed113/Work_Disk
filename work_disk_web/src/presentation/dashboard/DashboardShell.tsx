import type { DashboardModel } from './model/dashboard'

const EMPTY_MODEL: DashboardModel = { profile: null, capabilities: [], activities: [], notifications: [], summary: [], statusStrip: [] }

export function DashboardShell({ model = EMPTY_MODEL }: { model?: DashboardModel }) {
  void model
  return <main className="wd-dashboard-shell" id="dashboard" style={{ background: '#e8f7e8', minHeight: '100%' }}>
    <div className="wd-dashboard-pagebar">
      <h1 style={{
        background: 'linear-gradient(135deg, #00eaff 0%, #7c3cff 48%, #ff2bd6 100%)',
        WebkitBackgroundClip: 'text',
        backgroundClip: 'text',
        WebkitTextFillColor: 'transparent',
        textShadow: '0 2px 0 rgba(0, 70, 120, .9), 0 4px 0 rgba(35, 15, 90, .8), 0 7px 18px rgba(0, 234, 255, .35), 0 9px 24px rgba(255, 43, 214, .25)',
        letterSpacing: '0.04em',
        fontWeight: 800
      }}>Dashboard</h1>
    </div>
  </main>
}
