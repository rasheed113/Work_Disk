export const FOOTER_ITEMS = [
  { id: 'work-disk', label: 'WORK_DISK' },
  { id: 'workspace', label: 'Workspace' },
] as const

export function Footer() {
  return (
    <footer className="wd-footer" aria-label="Work_Disk footer" style={{
      background: 'linear-gradient(135deg, #16405a 0%, #28657d 45%, #4a2b70 100%)',
      borderTop: '1px solid rgba(0, 234, 255, .65)',
      boxShadow: '0 -5px 18px rgba(0, 234, 255, .16), inset 0 1px 0 rgba(255,255,255,.2)',
      color: '#ffffff'
    }}>
      <div className="wd-footer__brand" style={{
        color: '#ffffff',
        textShadow: '0 2px 0 rgba(0, 40, 65, .9), 0 4px 10px rgba(0, 0, 0, .45)'
      }}>{FOOTER_ITEMS[0].label}</div>
      <div className="wd-footer__meta" style={{
        color: '#ffffff',
        textShadow: '0 2px 0 rgba(0, 40, 65, .85), 0 4px 10px rgba(0, 0, 0, .4)'
      }}>{FOOTER_ITEMS[1].label}</div>
    </footer>
  )
}
