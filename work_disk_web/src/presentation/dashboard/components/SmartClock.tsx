import { useEffect, useState } from 'react'

export function SmartClock() {
  const [now, setNow] = useState(() => new Date())

  useEffect(() => {
    const timer = window.setInterval(() => setNow(new Date()), 1000)
    return () => window.clearInterval(timer)
  }, [])

  const time = now.toLocaleTimeString(undefined, {
    hour: '2-digit',
    minute: '2-digit',
    second: '2-digit',
  })
  const day = now.toLocaleDateString(undefined, { weekday: 'long' })
  const date = now.toLocaleDateString(undefined, {
    day: '2-digit',
    month: 'long',
    year: 'numeric',
  })

  return (
    <time
      className="wd-smart-clock"
      dateTime={now.toISOString()}
      aria-label={`${time}, ${day}, ${date}`}
    >
      <span className="wd-smart-clock__time">{time}</span>
      <span className="wd-smart-clock__meta" aria-hidden="true">
        <span className="wd-smart-clock__day">{day}</span>
        <span className="wd-smart-clock__date">{date}</span>
      </span>
    </time>
  )
}
