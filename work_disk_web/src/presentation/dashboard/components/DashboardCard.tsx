import type { ReactNode } from 'react'
import type { DashboardCardId } from '../model/dashboard'

interface Props { id: DashboardCardId; title: string; children: ReactNode; hidden?: boolean; pinned?: boolean; onHide?: () => void; onPin?: () => void; onMoveUp?: () => void; onMoveDown?: () => void }

export function DashboardCard({ id, title, children, hidden = false, pinned = false, onHide, onPin, onMoveUp, onMoveDown }: Props) {
  if (hidden) return null
  return (
    <section className="wd-dashboard-card" data-card-id={id} aria-label={title}>
      <header className="wd-dashboard-card__header">
        <h2>{title}</h2>
        <div className="wd-dashboard-card__controls">
          {onPin && <button type="button" onClick={onPin} aria-pressed={pinned}>{pinned ? 'Unpin' : 'Pin'}</button>}
          {onMoveUp && <button type="button" onClick={onMoveUp} aria-label={`Move ${title} up`}>↑</button>}
          {onMoveDown && <button type="button" onClick={onMoveDown} aria-label={`Move ${title} down`}>↓</button>}
          {onHide && <button type="button" onClick={onHide}>Hide</button>}
        </div>
      </header>
      <div className="wd-dashboard-card__body">{children}</div>
    </section>
  )
}
