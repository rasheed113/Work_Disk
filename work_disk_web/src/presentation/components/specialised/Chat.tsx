import { Card } from '../containers/Card'
export function Chat({author,message}:{author:string;message:string}){return <Card><strong>{author}</strong><p>{message}</p></Card>}
