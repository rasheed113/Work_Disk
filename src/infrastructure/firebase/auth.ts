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

export async function loginWithGoogle(): Promise<void> {
  await firebaseAuthReady
  await signInWithPopup(firebaseAuth, new GoogleAuthProvider())
}

export async function logout(): Promise<void> {
  await firebaseAuthReady
  await signOut(firebaseAuth)
}
