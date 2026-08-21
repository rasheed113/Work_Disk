import type { PropsWithChildren } from 'react'
export function Stack({children}:{children:React.ReactNode}){return <div style={{display:'flex',flexDirection:'column',gap:'var(--wd-space-md)'}}>{children}</div>}
