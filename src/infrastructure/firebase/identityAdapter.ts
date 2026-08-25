import { onAuthStateChanged, type User } from 'firebase/auth'
import type { IdentityPort } from '../../social/application/ports'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import { firebaseAuth } from './config'

export function authenticatedIdentity(user: User | null): AuthenticatedIdentity | null {
  if (!user) return null
  const email = user.email ?? user.providerData.find(provider => Boolean(provider.email))?.email
  return email ? { userId: user.uid, email } : null
}

export class FirebaseIdentityAdapter implements IdentityPort {
  currentIdentity(): AuthenticatedIdentity | null {
    return authenticatedIdentity(firebaseAuth.currentUser)
  }
}

export function subscribeIdentity(onChange: (identity: AuthenticatedIdentity | null) => void): () => void {
  return onAuthStateChanged(firebaseAuth, user => onChange(authenticatedIdentity(user)))
}
