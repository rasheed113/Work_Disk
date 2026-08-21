import { Card } from '../containers/Card'
export function Feed({title,body}:{title:string;body:string}){return <Card><strong>{title}</strong><p>{body}</p></Card>}
