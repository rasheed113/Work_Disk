import { useEffect, useState, type ReactElement } from 'react'
import { AuthGate } from './AuthGate'
import { PasswordResetPage } from './PasswordResetPage'
import { SocialApp } from './SocialApp'
import { subscribeIdentity } from '../infrastructure/firebase/identityAdapter'
import type { AuthenticatedIdentity } from '../social/domain/identity'

export function App(): ReactElement {
  const resetMode = new URLSearchParams(window.location.search).get('mode') === 'resetPassword'
  const [identity, setIdentity] = useState<AuthenticatedIdentity | null>(null)
  const [authResolved, setAuthResolved] = useState(false)

  useEffect(() => {
    if (resetMode) return
    return subscribeIdentity(nextIdentity => {
      setIdentity(nextIdentity)
      setAuthResolved(true)
    })
  }, [resetMode])

  if (resetMode) return <PasswordResetPage />
  if (!authResolved) return <div className="loading">Checking your secure session…</div>
  return identity
    ? <SocialApp identity={identity} onDashboard={() => window.location.assign('/dashboard')} />
    : <AuthGate />
}
