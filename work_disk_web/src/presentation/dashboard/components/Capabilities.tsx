import type { DashboardCapability } from '../model/dashboard'

export function Capabilities({ capabilities }: { capabilities: DashboardCapability[] }) {
  const eligible = capabilities.filter((capability) => capability.available)
  return eligible.length ? <div className="wd-capability-grid">{eligible.map((capability) => <article key={capability.id}><h3>{capability.title}</h3><p>{capability.description}</p></article>)}</div> : <p>No eligible capabilities are available in this context.</p>
}
