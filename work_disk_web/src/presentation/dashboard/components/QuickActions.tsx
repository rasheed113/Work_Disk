export interface DashboardQuickAction { id: string; label: string; onSelect: () => void }

export function QuickActions({ actions }: { actions: DashboardQuickAction[] }) {
  return <div className="wd-action-list">{actions.length ? actions.map((action) => <button key={action.id} type="button" onClick={action.onSelect}>{action.label}</button>) : <p>No quick actions are available.</p>}</div>
}
