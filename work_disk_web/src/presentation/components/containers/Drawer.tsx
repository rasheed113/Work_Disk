import type { PropsWithChildren } from 'react'
export function Drawer({children,open,onClose}:{children:React.ReactNode;open:boolean;onClose:()=>void}){if(!open)return null;return <aside aria-label="Drawer"><button type="button" aria-label="Close" onClick={onClose}>×</button>{children}</aside>}
