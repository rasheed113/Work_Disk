import {
  createUserWithEmailAndPassword,
  getRedirectResult,
  GoogleAuthProvider,
  signInWithEmailAndPassword,
  signInWithPopup,
  signInWithRedirect,
  signOut,
  type UserCredential,
} from 'firebase/auth'
import { firebaseAuth } from './config'

export async function register(email: string, password: string): Promise<void> {
  await createUserWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export async function login(email: string, password: string): Promise<void> {
  await signInWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export async function loginWithGoogle(): Promise<void> {
  const provider = new GoogleAuthProvider()
  if (window.matchMedia('(max-width: 767px)').matches) {
    await signInWithRedirect(firebaseAuth, provider)
    return
  }
  await signInWithPopup(firebaseAuth, provider)
}

export async function resolveGoogleRedirect(): Promise<UserCredential | null> {
  return getRedirectResult(firebaseAuth)
}

export async function logout(): Promise<void> {
  await signOut(firebaseAuth)
}
