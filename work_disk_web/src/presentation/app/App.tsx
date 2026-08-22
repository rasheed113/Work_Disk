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
    <section className="wd-feature-card wd-feature-card--empty" aria-labelledby="destination-title">
      <span className="wd-feature-card__label">FEATURE SURFACE</span>
      <h2 id="destination-title">{title}</h2>
      <p>This destination is registered in the workspace shell but its feature implementation is deferred.</p>
    </section>
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
        <Route path="settings" element={<EmptyWorkspaceDestination title="Settings" />} />
      </Route>
      <Route path="/profile" element={<Navigate to="/workspace/profile" replace />} />
      <Route path="/dashboard" element={<Navigate to="/workspace/dashboard" replace />} />
      <Route path="/settings" element={<Navigate to="/workspace/settings" replace />} />
      <Route path="*" element={<Navigate to="/workspace/dashboard" replace />} />
    </Routes>
  )
}
