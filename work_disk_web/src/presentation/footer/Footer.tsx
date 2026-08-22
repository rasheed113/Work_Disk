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
      color: '#f7fbff',
      textShadow: '0 2px 0 rgba(0,0,0,.45), 0 4px 12px rgba(0, 234, 255, .22)'
    }}>
      <div className="wd-footer__brand" style={{
        background: 'linear-gradient(135deg, #00eaff 0%, #7c3cff 50%, #ff2bd6 100%)',
        WebkitBackgroundClip: 'text',
        backgroundClip: 'text',
        WebkitTextFillColor: 'transparent',
        textShadow: '0 2px 0 rgba(0, 60, 100, .75), 0 4px 0 rgba(45, 10, 90, .65), 0 7px 18px rgba(0, 234, 255, .28)'
      }}>{FOOTER_ITEMS[0].label}</div>
      <div className="wd-footer__meta" style={{
        background: 'linear-gradient(135deg, #7dffcf 0%, #00eaff 50%, #9b7cff 100%)',
        WebkitBackgroundClip: 'text',
        backgroundClip: 'text',
        WebkitTextFillColor: 'transparent',
        textShadow: '0 2px 0 rgba(0, 55, 75, .65), 0 4px 14px rgba(0, 234, 255, .2)'
      }}>{FOOTER_ITEMS[1].label}</div>
    </footer>
  )
}
