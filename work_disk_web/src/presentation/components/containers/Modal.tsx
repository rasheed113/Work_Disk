import type { PropsWithChildren } from 'react'
export function Modal({children,open,onClose}:{children:React.ReactNode;open:boolean;onClose:()=>void}){if(!open)return null;return <div role="dialog" aria-modal="true"><button type="button" aria-label="Close" onClick={onClose}>×</button>{children}</div>}
