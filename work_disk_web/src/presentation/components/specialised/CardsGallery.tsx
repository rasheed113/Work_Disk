import { getEligibleComponents } from '../registry/componentRegistry'
export function CardsGallery({onSelect}:{onSelect:(id:string)=>void}){return <div aria-label="Cards Gallery">{getEligibleComponents().map(c=><button key={c.id} type="button" onClick={()=>onSelect(c.id)}>{c.name}</button>)}</div>}
