import { Navigate, Route, Routes } from 'react-router-dom'
import { DashboardShell } from '../dashboard/DashboardShell'
import '../dashboard/dashboard.css'

function PresentationHome() {
  return <DashboardShell />
}

export function App() {
  return <Routes>
    <Route path="/" element={<PresentationHome />} />
    <Route path="/dashboard" element={<DashboardShell />} />
    <Route path="*" element={<Navigate to="/dashboard" replace />} />
  </Routes>
}
