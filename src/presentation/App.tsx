import { useEffect, useState } from 'react'
import { AuthGate } from './AuthGate'
import { SocialApp } from './SocialApp'
import { firebaseAuth } from '../infrastructure/firebase/config'

export function App(): JSX.Element {
  const [authenticated, setAuthenticated] = useState(firebaseAuth.currentUser !== null)

  useEffect(() => {
    return firebaseAuth.onAuthStateChanged(user => setAuthenticated(user !== null))
  }, [])

  return authenticated ? <SocialApp onDashboard={() => window.location.assign('/dashboard')} /> : <AuthGate />
}
