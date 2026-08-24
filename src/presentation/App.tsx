import { useEffect, useState, type ReactElement } from 'react'
import { AuthGate } from './AuthGate'
import { SocialApp } from './SocialApp'
import { firebaseAuth } from '../infrastructure/firebase/config'

export function App(): ReactElement {
  const [authenticated, setAuthenticated] = useState(firebaseAuth.currentUser !== null)
  useEffect(() => firebaseAuth.onAuthStateChanged(user => setAuthenticated(user !== null)), [])
  return authenticated ? <SocialApp onDashboard={() => window.location.assign('/dashboard')} /> : <AuthGate />
}
