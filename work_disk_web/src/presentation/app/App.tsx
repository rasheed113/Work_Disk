import { Navigate, Route, Routes } from 'react-router-dom'

function PresentationHome() {
  return (
    <main>
      <h1>Work_Disk Web</h1>
      <p>Presentation foundation is active.</p>
    </main>
  )
}

export function App() {
  return (
    <Routes>
      <Route path="/" element={<PresentationHome />} />
      <Route path="*" element={<Navigate to="/" replace />} />
    </Routes>
  )
}
