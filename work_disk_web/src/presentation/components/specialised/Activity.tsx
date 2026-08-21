import { Card } from '../containers/Card'
export function Activity({label,time}:{label:string;time?:string}){return <Card><span>{label}</span>{time&&<small>{time}</small>}</Card>}
