import type { PropsWithChildren } from 'react'
import './surface.css'

export function Surface({ children, className = '' }: PropsWithChildren<{ className?: string }>) {
  return <div className={`wd-surface ${className}`}>{children}</div>
}
