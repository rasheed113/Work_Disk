import { lazy, Suspense, useEffect, useState, type ReactElement } from 'react'
import { subscribeIdentity } from '../infrastructure/firebase/identityAdapter'
import type { AuthenticatedIdentity } from '../social/domain/identity'

const AuthGate = lazy(() => import('./AuthGate').then(module => ({ default: module.AuthGate })))
const PasswordResetPage = lazy(() => import('./PasswordResetPage').then(module => ({ default: module.PasswordResetPage })))
const SocialApp = lazy(() => import('./SocialApp').then(module => ({ default: module.SocialApp })))

function PresentationFallback(): ReactElement {
  return <div className="loading" aria-live="polite">Loading Work_Disk…</div>
}

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

  if (resetMode) {
    return <Suspense fallback={<PresentationFallback />}><PasswordResetPage /></Suspense>
  }

  if (!authResolved) return <div className="loading" aria-live="polite">Checking your secure session…</div>

  return <Suspense fallback={<PresentationFallback />}>
    {identity
      ? <SocialApp identity={identity} onDashboard={() => window.location.assign('/dashboard')} />
      : <AuthGate />}
  </Suspense>
}
