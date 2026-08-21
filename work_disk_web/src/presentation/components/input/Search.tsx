import { TextInput } from './TextInput'
export function Search({value,onChange,placeholder='Search'}:{value:string;onChange:(value:string)=>void;placeholder?:string}){return <TextInput type="search" aria-label={placeholder} value={value} onChange={e=>onChange(e.target.value)} placeholder={placeholder}/>} 
