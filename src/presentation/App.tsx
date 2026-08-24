import { useEffect, useState, type ReactElement } from 'react'
import { AuthGate } from './AuthGate'
import { SocialApp } from './SocialApp'
import { firebaseAuth } from '../infrastructure/firebase/config'

export function App(): ReactElement {
  const [authenticated, setAuthenticated] = useState(firebaseAuth.currentUser !== null)

  useEffect(() => {
    const unsubscribe = firebaseAuth.onAuthStateChanged(user => {
      setAuthenticated(user !== null)
    })
    return unsubscribe
  }, [])

  return authenticated ? <SocialApp onDashboard={() => window.location.assign('/dashboard')} /> : <AuthGate />
}
