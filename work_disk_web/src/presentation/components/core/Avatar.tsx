export function Avatar({src,alt}: {src?:string; alt:string}) { return src ? <img src={src} alt={alt} /> : <span role="img" aria-label={alt}>{alt.slice(0,1).toUpperCase()}</span> }
