import { useEffect, useState, type ReactElement } from 'react'
import { AuthGate } from './AuthGate'
import { SocialApp } from './SocialApp'
import { firebaseAuth } from '../infrastructure/firebase/config'
import { resolveGoogleRedirect } from '../infrastructure/firebase/auth'

export function App(): ReactElement {
  const [authenticated, setAuthenticated] = useState(firebaseAuth.currentUser !== null)

  useEffect(() => {
    let active = true

    const unsubscribe = firebaseAuth.onAuthStateChanged(user => {
      if (active) setAuthenticated(user !== null)
    })

    void resolveGoogleRedirect().catch(() => null)

    return () => {
      active = false
      unsubscribe()
    }
  }, [])

  return authenticated ? <SocialApp onDashboard={() => window.location.assign('/dashboard')} /> : <AuthGate />
}
