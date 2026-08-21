import type { PropsWithChildren } from 'react'
import { Card } from '../containers/Card'
export function DashboardCard({title,children}:{title:string}&PropsWithChildren){return <Card><h3>{title}</h3>{children}</Card>}
