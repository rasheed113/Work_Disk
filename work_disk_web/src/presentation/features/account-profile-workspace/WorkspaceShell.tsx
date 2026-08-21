import { NavLink, Outlet } from 'react-router-dom'
import { WORKSPACE_NAV_ITEMS } from './model'

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

      <nav className="wd-workspace-nav" aria-label="Workspace navigation">
        {WORKSPACE_NAV_ITEMS.map((item) => (
          <NavLink
            key={item.to}
            to={item.to}
            className={({ isActive }) => `wd-workspace-nav__item${isActive ? ' is-active' : ''}`}
          >
            <strong>{item.label}</strong>
            <span>{item.description}</span>
          </NavLink>
        ))}
      </nav>

      <section className="wd-workspace-content">
        <Outlet />
      </section>
    </main>
  )
}
