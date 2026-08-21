import { useEffect, useState } from 'react'

export function SmartClock() {
  const [now, setNow] = useState(() => new Date())
  useEffect(() => { const timer = window.setInterval(() => setNow(new Date()), 1000); return () => window.clearInterval(timer) }, [])
  return <time dateTime={now.toISOString()}>{now.toLocaleTimeString()}</time>
}
