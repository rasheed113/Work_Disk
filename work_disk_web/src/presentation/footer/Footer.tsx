export const FOOTER_ITEMS = [
  { id: 'work-disk', label: 'WORK_DISK' },
  { id: 'workspace', label: 'Workspace' },
] as const

const FOOTER_3D_TEXT_STYLE = {
  fontFamily: '"Arial Black", Impact, Haettenschweiler, sans-serif',
  fontWeight: 950,
  letterSpacing: '.045em',
  color: '#d9dde3',
  WebkitTextStroke: '1px #69727c',
  textShadow: '0 1px 0 #ffffff, 0 2px 0 #b8bec6, 0 3px 0 #929aa4, 0 5px 0 #68717b, 0 7px 0 #454d56, 0 9px 13px rgba(0,0,0,.38)',
  filter: 'drop-shadow(0 2px 3px rgba(0,0,0,.22))',
} as const

export function Footer() {
  return (
    <footer className="wd-footer" aria-label="Work_Disk footer" style={{
      background: 'linear-gradient(135deg, #16405a 0%, #28657d 45%, #4a2b70 100%)',
      borderTop: '1px solid rgba(0, 234, 255, .65)',
      boxShadow: '0 -5px 18px rgba(0, 234, 255, .16), inset 0 1px 0 rgba(255,255,255,.2)',
      color: '#d9dde3'
    }}>
      <div className="wd-footer__brand" style={{
        ...FOOTER_3D_TEXT_STYLE,
        fontSize: '1.05rem',
        transform: 'perspective(500px) rotateX(2deg)',
      }}>{FOOTER_ITEMS[0].label}</div>
      <div className="wd-footer__meta" style={{
        ...FOOTER_3D_TEXT_STYLE,
        fontSize: '.9rem',
        opacity: .96,
      }}>{FOOTER_ITEMS[1].label}</div>
    </footer>
  )
}
