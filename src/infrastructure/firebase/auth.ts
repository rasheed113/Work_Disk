import {
  GoogleAuthProvider,
  createUserWithEmailAndPassword,
  signInWithEmailAndPassword,
  signInWithPopup,
  signOut,
} from 'firebase/auth'
import { firebaseAuth, firebaseAuthReady } from './config'

export async function register(email: string, password: string): Promise<void> {
  await firebaseAuthReady
  await createUserWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export async function login(email: string, password: string): Promise<void> {
  await firebaseAuthReady
  await signInWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export function loginWithGoogle(): Promise<void> {
  // Popup creation must happen directly from the click's user activation.
  // Awaiting firebaseAuthReady here can lose that activation on mobile Chrome.
  const provider = new GoogleAuthProvider()
  provider.setCustomParameters({ prompt: 'select_account' })
  return signInWithPopup(firebaseAuth, provider)
}

export async function logout(): Promise<void> {
  await firebaseAuthReady
  await signOut(firebaseAuth)
}
