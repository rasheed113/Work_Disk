import type { PropsWithChildren } from 'react'
export function Section({children,title}:{children:React.ReactNode;title?:string}){return <section aria-label={title}>{title&&<h2>{title}</h2>}{children}</section>}
