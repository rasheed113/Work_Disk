import { NavLink } from 'react-router-dom'

const ITEMS = [
  { to: '/workspace/dashboard', label: 'Dashboard' },
  { to: '/workspace/finance', label: 'Finance' },
  { to: '/workspace/history', label: 'History' },
  { to: '/workspace/settings', label: 'Settings' },
  { to: '/workspace/profile', label: 'Profile' },
]

export function Navigation() {
  return <nav aria-label="Workspace feature navigation"><ul className="wd-dashboard-nav">{ITEMS.map((item) => <li key={item.to}><NavLink to={item.to}>{item.label}</NavLink></li>)}</ul></nav>
}
