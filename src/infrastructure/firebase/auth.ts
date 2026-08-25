import {
  GoogleAuthProvider,
  createUserWithEmailAndPassword,
  sendPasswordResetEmail,
  signInWithEmailAndPassword,
  signInWithPopup,
  signOut,
} from 'firebase/auth'
import { firebaseAuth } from './config'

function normaliseEmail(email: string): string {
  return email.trim().toLowerCase()
}

function credentials(email: string, password: string): { email: string; password: string } {
  const normalisedEmail = normaliseEmail(email)
  if (!normalisedEmail) throw new Error('Please enter your email address.')
  if (!password) throw new Error('Please enter your password.')
  return { email: normalisedEmail, password }
}

export async function register(email: string, password: string): Promise<void> {
  const input = credentials(email, password)
  await createUserWithEmailAndPassword(firebaseAuth, input.email, input.password)
}

export async function login(email: string, password: string): Promise<void> {
  const input = credentials(email, password)
  await signInWithEmailAndPassword(firebaseAuth, input.email, input.password)
}

export async function resetPassword(email: string): Promise<void> {
  const normalisedEmail = normaliseEmail(email)
  if (!normalisedEmail) throw new Error('Please enter your email address.')
  const actionCodeSettings = {
    url: `${window.location.origin}/?mode=resetPassword`,
    handleCodeInApp: false,
  }
  await sendPasswordResetEmail(firebaseAuth, normalisedEmail, actionCodeSettings)
}

// Keep the proven Google popup flow unchanged.
export function loginWithGoogle(): Promise<void> {
  const provider = new GoogleAuthProvider()
  provider.setCustomParameters({ prompt: 'select_account' })
  return signInWithPopup(firebaseAuth, provider).then(() => undefined)
}

export async function logout(): Promise<void> {
  await signOut(firebaseAuth)
}
