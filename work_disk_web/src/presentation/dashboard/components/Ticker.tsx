export function Ticker({ message = 'Work_Disk dashboard ready' }: { message?: string }) {
  return <div className="wd-dashboard-ticker" role="status">{message}</div>
}
