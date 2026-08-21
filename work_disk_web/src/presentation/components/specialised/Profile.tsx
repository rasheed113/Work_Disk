import { Card } from '../containers/Card'
export function Profile({name,subtitle}:{name:string;subtitle?:string}){return <Card><strong>{name}</strong>{subtitle&&<p>{subtitle}</p>}</Card>}
