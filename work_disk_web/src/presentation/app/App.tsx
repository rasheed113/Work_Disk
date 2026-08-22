import { Navigate, Route, Routes } from 'react-router-dom'
import { DashboardShell } from '../dashboard/DashboardShell'
import '../dashboard/dashboard.css'
import { AccountProfileSurface } from '../features/account-profile-workspace/AccountProfileSurface'
import { WorkspaceShell } from '../features/account-profile-workspace/WorkspaceShell'
import '../features/account-profile-workspace/workspace.css'

function PresentationHome() {
  return <Navigate to="/workspace/dashboard" replace />
}

function EmptyWorkspaceDestination({ title }: { title: string }) {
  return (
    <main className="wd-dashboard-shell" id={`${title.toLowerCase()}-page`} style={{ background: '#e8f7e8', minHeight: '100%' }}>
      <div className="wd-dashboard-pagebar">
        <h1 style={{
          background: 'linear-gradient(135deg, #00eaff 0%, #7c3cff 48%, #ff2bd6 100%)',
          WebkitBackgroundClip: 'text',
          backgroundClip: 'text',
          WebkitTextFillColor: 'transparent',
          textShadow: '0 2px 0 rgba(0, 70, 120, .9), 0 4px 0 rgba(35, 15, 90, .8), 0 7px 18px rgba(0, 234, 255, .35), 0 9px 24px rgba(255, 43, 214, .25)',
          letterSpacing: '0.04em',
          fontWeight: 800
        }}>{title}</h1>
      </div>
    </main>
  )
}

export function App() {
  return (
    <Routes>
      <Route path="/" element={<PresentationHome />} />
      <Route path="/workspace" element={<WorkspaceShell />}>
        <Route index element={<Navigate to="/dashboard" replace />} />
        <Route path="profile" element={<AccountProfileSurface model={null} />} />
        <Route path="dashboard" element={<DashboardShell />} />
        <Route path="history" element={<EmptyWorkspaceDestination title="History" />} />
        <Route path="finance" element={<EmptyWorkspaceDestination title="Finance" />} />
        <Route path="settings" element={<EmptyWorkspaceDestination title="Settings" />} />
      </Route>
      <Route path="/profile" element={<Navigate to="/workspace/profile" replace />} />
      <Route path="/dashboard" element={<Navigate to="/workspace/dashboard" replace />} />
      <Route path="/history" element={<Navigate to="/workspace/history" replace />} />
      <Route path="/finance" element={<Navigate to="/workspace/finance" replace />} />
      <Route path="/settings" element={<Navigate to="/workspace/settings" replace />} />
      <Route path="*" element={<Navigate to="/workspace/dashboard" replace />} />
    </Routes>
  )
}
