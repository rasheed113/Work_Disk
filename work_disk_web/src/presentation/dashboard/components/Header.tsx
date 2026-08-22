import type { DashboardProfile } from '../model/dashboard'

export function Header({ profile }: { profile: DashboardProfile | null }) {
  return <header className="wd-dashboard-header">
    <div><strong>WORK_DISK</strong><span>Workspace</span></div>
    <div className="wd-dashboard-header__context">{profile ? profile.displayName : 'Account context'}</div>
  </header>
}
