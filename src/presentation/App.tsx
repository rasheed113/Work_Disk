import { useEffect, useState, type ReactElement } from 'react'
import { AuthGate } from './AuthGate'
import { SocialApp } from './SocialApp'
import { firebaseAuth } from '../infrastructure/firebase/config'
import { resolveGoogleRedirect } from '../infrastructure/firebase/auth'

export function App(): ReactElement {
  const [authenticated, setAuthenticated] = useState(firebaseAuth.currentUser !== null)
  const [authReady, setAuthReady] = useState(false)

  useEffect(() => {
    let active = true

    void resolveGoogleRedirect()
      .catch(() => null)
      .finally(() => {
        if (active) setAuthReady(true)
      })

    const unsubscribe = firebaseAuth.onAuthStateChanged(user => {
      if (active) setAuthenticated(user !== null)
    })

    return () => {
      active = false
      unsubscribe()
    }
  }, [])

  if (!authReady) {
    return <main className="auth-shell"><section className="auth-card"><div className="brand-mark">WD</div><h1>Work_Disk Social</h1><p>Checking your secure session…</p></section></main>
  }

  return authenticated ? <SocialApp onDashboard={() => window.location.assign('/dashboard')} /> : <AuthGate />
}
