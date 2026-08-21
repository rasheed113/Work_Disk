import { Card } from '../containers/Card'
export function Notification({title,message}:{title:string;message:string}){return <Card><strong>{title}</strong><p>{message}</p></Card>}
