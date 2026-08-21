import type { ButtonHTMLAttributes } from 'react'
export function Button({ children, ...props }: ButtonHTMLAttributes<HTMLButtonElement>) { return <button type={props.type ?? 'button'} {...props}>{children}</button> }
