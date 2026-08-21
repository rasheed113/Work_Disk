import type { DashboardCardDefinition, DashboardCardId } from '../model/dashboard'

export function CardsGallery({ definitions, hidden, onUnhide }: { definitions: readonly DashboardCardDefinition[]; hidden: DashboardCardId[]; onUnhide: (id: DashboardCardId) => void }) {
  return <div className="wd-gallery">{definitions.map((definition) => <article key={definition.id}><h3>{definition.title}</h3><p>{definition.description}</p>{hidden.includes(definition.id) && <button type="button" onClick={() => onUnhide(definition.id)}>Unhide</button>}</article>)}</div>
}
