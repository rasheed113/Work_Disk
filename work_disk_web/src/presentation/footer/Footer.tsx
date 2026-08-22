const FOOTER_ITEMS = [
  { id: 'work-disk', label: 'WORK_DISK' },
  { id: 'workspace', label: 'Workspace' },
] as const

export function Footer() {
  return (
    <footer className="wd-footer" aria-label="Work_Disk footer">
      <div className="wd-footer__brand">{FOOTER_ITEMS[0].label}</div>
      <div className="wd-footer__meta">{FOOTER_ITEMS[1].label}</div>
    </footer>
  )
}
