export function IconAction({label,onClick,children}:{label:string;onClick:()=>void;children:React.ReactNode}){return <button type="button" aria-label={label} onClick={onClick}>{children}</button>}
