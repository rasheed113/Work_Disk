import { useEffect, useState, type ReactElement } from 'react'
import { AuthGate } from './AuthGate'
import { PasswordResetPage } from './PasswordResetPage'
import { SocialApp } from './SocialApp'
import { firebaseAuth } from '../infrastructure/firebase/config'

export function App(): ReactElement {
  const resetMode = new URLSearchParams(window.location.search).get('mode') === 'resetPassword'
  const [authenticated, setAuthenticated] = useState(firebaseAuth.currentUser !== null)

  useEffect(() => {
    if (resetMode) return
    const unsubscribe = firebaseAuth.onAuthStateChanged(user => {
      setAuthenticated(user !== null)
    })
    return unsubscribe
  }, [resetMode])

  if (resetMode) return <PasswordResetPage />
  return authenticated ? <SocialApp onDashboard={() => window.location.assign('/dashboard')} /> : <AuthGate />
}
