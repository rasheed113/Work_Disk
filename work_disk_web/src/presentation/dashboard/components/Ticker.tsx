import type { DashboardStatusStripItem } from '../model/dashboard'

export function StatusStrip({ items }: { items: DashboardStatusStripItem[] }) {
  if (items.length === 0) return null

  const content = items.map((item) => (
    <span key={item.id} className="wd-dashboard-status-strip__item">
      {item.text}
    </span>
  ))

  return (
    <section className="wd-dashboard-status-strip" aria-label="Work_Disk status stream" role="status">
      <div className="wd-dashboard-status-strip__track">
        <div className="wd-dashboard-status-strip__run">{content}</div>
        <div className="wd-dashboard-status-strip__run" aria-hidden="true">{content}</div>
      </div>
    </section>
  )
}
