import { onAuthStateChanged, type User } from 'firebase/auth'
import type { IdentityPort } from '../../social/application/ports'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import { firebaseAuth } from './config'

export class FirebaseIdentityAdapter implements IdentityPort {
  currentIdentity(): AuthenticatedIdentity | null {
    const user: User | null = firebaseAuth.currentUser
    return user && user.email
      ? { userId: user.uid, email: user.email }
      : null
  }
}

export function subscribeIdentity(onChange: (identity: AuthenticatedIdentity | null) => void): () => void {
  return onAuthStateChanged(firebaseAuth, user => {
    onChange(user && user.email ? { userId: user.uid, email: user.email } : null)
  })
}
