import type { DashboardCardDefinition, DashboardCardId } from '../model/dashboard'

interface Props {
  definitions: readonly DashboardCardDefinition[]
  order: DashboardCardId[]
  hidden: DashboardCardId[]
  pinned: DashboardCardId[]
  onHide: (id: DashboardCardId) => void
  onUnhide: (id: DashboardCardId) => void
  onTogglePin: (id: DashboardCardId) => void
  onMoveUp: (id: DashboardCardId) => void
  onMoveDown: (id: DashboardCardId) => void
  onReset: () => void
}

export function Customisation({ definitions, order, hidden, pinned, onHide, onUnhide, onTogglePin, onMoveUp, onMoveDown, onReset }: Props) {
  return <section className="wd-customisation-panel" aria-label="Customize dashboard">
    <div className="wd-customisation-panel__heading">
      <div>
        <strong>Customize Dashboard</strong>
        <p>Manage visibility, pinning and card order without changing feature or domain data.</p>
      </div>
      <button type="button" onClick={onReset}>Reset to Default</button>
    </div>
    <div className="wd-customisation-list">
      {definitions.filter((definition) => definition.removable).map((definition) => {
        const index = order.indexOf(definition.id)
        const isHidden = hidden.includes(definition.id)
        const isPinned = pinned.includes(definition.id)
        return <div key={definition.id} className="wd-customisation-item">
          <div className="wd-customisation-item__identity">
            <strong>{definition.title}</strong>
            {isHidden && <span>Hidden</span>}
            {isPinned && <span>Pinned</span>}
          </div>
          <div className="wd-customisation-item__actions">
            <button type="button" onClick={() => isHidden ? onUnhide(definition.id) : onHide(definition.id)}>{isHidden ? 'Unhide' : 'Hide'}</button>
            <button type="button" onClick={() => onTogglePin(definition.id)} aria-pressed={isPinned}>{isPinned ? 'Unpin' : 'Pin'}</button>
            <button type="button" onClick={() => onMoveUp(definition.id)} disabled={index <= 0} aria-label={`Move ${definition.title} up`}>↑</button>
            <button type="button" onClick={() => onMoveDown(definition.id)} disabled={index < 0 || index >= order.length - 1} aria-label={`Move ${definition.title} down`}>↓</button>
          </div>
        </div>
      })}
    </div>
  </section>
}
