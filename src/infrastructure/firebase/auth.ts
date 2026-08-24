import {
  GoogleAuthProvider,
  browserLocalPersistence,
  createUserWithEmailAndPassword,
  getRedirectResult,
  setPersistence,
  signInWithEmailAndPassword,
  signInWithPopup,
  signOut,
} from 'firebase/auth'
import { firebaseAuth } from './config'

const authPersistenceReady = setPersistence(firebaseAuth, browserLocalPersistence)

export async function register(email: string, password: string): Promise<void> {
  await authPersistenceReady
  await createUserWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export async function login(email: string, password: string): Promise<void> {
  await authPersistenceReady
  await signInWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export function loginWithGoogle(): Promise<void> {
  const provider = new GoogleAuthProvider()
  provider.setCustomParameters({ prompt: 'select_account' })
  return signInWithPopup(firebaseAuth, provider).then(() => undefined)
}

export async function resolveGoogleRedirect(): Promise<void> {
  await authPersistenceReady
  await getRedirectResult(firebaseAuth)
}

export async function logout(): Promise<void> {
  await authPersistenceReady
  await signOut(firebaseAuth)
}
