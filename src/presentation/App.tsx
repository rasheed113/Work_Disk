import { useEffect, useState, type ReactElement } from 'react'
import { AuthGate } from './AuthGate'
import { SocialApp } from './SocialApp'
import { firebaseAuth } from '../infrastructure/firebase/config'
import { resolveGoogleRedirect } from '../infrastructure/firebase/auth'

export function App(): ReactElement {
  const [authenticated, setAuthenticated] = useState(firebaseAuth.currentUser !== null)
  const [authReady, setAuthReady] = useState(firebaseAuth.currentUser !== null)

  useEffect(() => {
    let active = true

    const unsubscribe = firebaseAuth.onAuthStateChanged(user => {
      if (!active) return
      setAuthenticated(user !== null)
      setAuthReady(true)
    })

    // Resolve a pending Google redirect without making the entire app wait on it.
    // onAuthStateChanged remains the authoritative session boundary.
    void resolveGoogleRedirect().catch(() => null)

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
