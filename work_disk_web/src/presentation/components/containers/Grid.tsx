import type { PropsWithChildren } from 'react'
export function Grid({children}:{children:React.ReactNode}){return <div style={{display:'grid',gridTemplateColumns:'repeat(auto-fit,minmax(220px,1fr))',gap:'var(--wd-space-md)'}}>{children}</div>}
