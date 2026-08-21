import type { DashboardCardDefinition, DashboardCardId } from '../model/dashboard'

interface Props { definitions: readonly DashboardCardDefinition[]; hidden: DashboardCardId[]; pinned: DashboardCardId[]; onHide: (id: DashboardCardId) => void; onUnhide: (id: DashboardCardId) => void; onTogglePin: (id: DashboardCardId) => void; onReset: () => void }

export function Customisation({ definitions, hidden, pinned, onHide, onUnhide, onTogglePin, onReset }: Props) {
  return <div className="wd-customisation"><p>Personalise your dashboard without deleting any feature or domain data.</p><div className="wd-customisation-list">{definitions.filter((definition) => definition.removable).map((definition) => { const isHidden = hidden.includes(definition.id); const isPinned = pinned.includes(definition.id); return <div key={definition.id}><span>{definition.title}</span><button type="button" onClick={() => isHidden ? onUnhide(definition.id) : onHide(definition.id)}>{isHidden ? 'Unhide' : 'Hide'}</button><button type="button" onClick={() => onTogglePin(definition.id)} aria-pressed={isPinned}>{isPinned ? 'Unpin' : 'Pin'}</button></div> })}</div><button type="button" onClick={onReset}>Reset to Default</button></div>
}
