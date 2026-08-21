import { Card } from '../containers/Card'
export function Capability({name,available=true}:{name:string;available?:boolean}){return <Card><strong>{name}</strong><span>{available?'Available':'Unavailable'}</span></Card>}
