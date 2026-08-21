import type { DashboardProfile } from '../model/dashboard'

export function Header({ profile }: { profile: DashboardProfile | null }) {
  return <header className="wd-dashboard-header"><div><strong>Work_Disk</strong><span>Dashboard</span></div><div className="wd-dashboard-context">{profile ? profile.displayName : 'Account context'}</div></header>
}
