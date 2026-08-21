import type { DashboardNotification } from '../model/dashboard'

export function Notifications({ items }: { items: DashboardNotification[] }) {
  return items.length ? <ul>{items.map((item) => <li key={item.id}><strong>{item.title}</strong>{!item.read && <span aria-label="Unread"> • unread</span>}<time dateTime={item.timestamp}> {item.timestamp}</time></li>)}</ul> : <p>No notifications are available.</p>
}
