import { Outlet } from 'react-router-dom'

export function WorkspaceShell() {
  return (
    <main className="wd-workspace-shell">
      <header className="wd-workspace-header">
        <div>
          <p className="wd-feature-surface__eyebrow">WORK_DISK</p>
          <h1>Workspace</h1>
          <p>One stable identity boundary with feature surfaces assembled around it.</p>
        </div>
      </header>

      <section className="wd-workspace-content">
        <Outlet />
      </section>
    </main>
  )
}
