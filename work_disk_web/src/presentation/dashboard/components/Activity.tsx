import type { DashboardActivityItem } from '../model/dashboard'

export function Activity({ items }: { items: DashboardActivityItem[] }) {
  return items.length ? <ul>{items.map((item) => <li key={item.id}><strong>{item.title}</strong><time dateTime={item.timestamp}> {item.timestamp}</time></li>)}</ul> : <p>No recent activity is available.</p>
}
