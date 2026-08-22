export const FOOTER_ITEMS = [
  { id: 'work-disk', label: 'WORK_DISK' },
  { id: 'workspace', label: 'Workspace' },
] as const

const FOOTER_3D_TEXT_STYLE = {
  fontFamily: '"Trebuchet MS", "Segoe UI", sans-serif',
  fontWeight: 800,
  letterSpacing: '.055em',
  color: '#e9f4ff',
  WebkitTextStroke: '0.5px rgba(255,255,255,.45)',
  textShadow: '0 1px 0 rgba(255,255,255,.75), 0 2px 0 rgba(30,74,105,.95), 0 4px 0 rgba(12,42,65,.9), 0 6px 10px rgba(0,0,0,.42)',
  filter: 'drop-shadow(0 2px 3px rgba(0,0,0,.2))',
} as const

export function Footer() {
  return (
    <footer className="wd-footer" aria-label="Work_Disk footer" style={{
      background: 'linear-gradient(135deg, #16405a 0%, #28657d 45%, #4a2b70 100%)',
      borderTop: '1px solid rgba(0, 234, 255, .65)',
      boxShadow: '0 -5px 18px rgba(0, 234, 255, .16), inset 0 1px 0 rgba(255,255,255,.2)',
      color: '#e9f4ff'
    }}>
      <div className="wd-footer__brand" style={{
        ...FOOTER_3D_TEXT_STYLE,
        fontSize: '1.02rem',
        transform: 'translateY(-1px) perspective(500px) rotateX(2deg)',
      }}>{FOOTER_ITEMS[0].label}</div>
      <div className="wd-footer__meta" style={{
        ...FOOTER_3D_TEXT_STYLE,
        fontSize: '.88rem',
        opacity: .94,
      }}>{FOOTER_ITEMS[1].label}</div>
    </footer>
  )
}
