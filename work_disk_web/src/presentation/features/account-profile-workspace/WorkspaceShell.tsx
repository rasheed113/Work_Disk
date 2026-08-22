import { Outlet } from 'react-router-dom'
import { Footer } from '../../footer/Footer'

export function WorkspaceShell() {
  return (
    <main className="wd-workspace-shell">
      <header className="wd-workspace-header" aria-label="Work_Disk workspace header">
        <div className="wd-workspace-brand">
          <span className="wd-workspace-brand__mark" aria-hidden="true">WD</span>
          <div className="wd-workspace-brand__copy">
            <span className="wd-workspace-brand__title">WORK_DISK</span>
            <span className="wd-workspace-brand__subtitle">WORKSPACE</span>
          </div>
        </div>
        <p className="wd-workspace-header__description">One stable identity boundary with feature surfaces assembled around it.</p>
      </header>

      <section className="wd-workspace-content" style={{ background: '#e8f7e8', margin: 0, padding: 0, border: 0 }}>
        <Outlet />
      </section>

      <Footer />
    </main>
  )
}
