import type { DashboardSummaryMetric } from '../model/dashboard'

export function Summary({ metrics }: { metrics: DashboardSummaryMetric[] }) {
  return <div className="wd-summary-grid">{metrics.length ? metrics.map((metric) => <div key={metric.id}><span>{metric.label}</span><strong>{metric.value}</strong></div>) : <p>No summary metrics are available.</p>}</div>
}
