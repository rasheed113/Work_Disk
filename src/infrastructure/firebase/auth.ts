import { createUserWithEmailAndPassword, signInWithEmailAndPassword, signOut } from 'firebase/auth'
import { firebaseAuth } from './config'

export async function register(email: string, password: string): Promise<void> {
  await createUserWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export async function login(email: string, password: string): Promise<void> {
  await signInWithEmailAndPassword(firebaseAuth, email.trim(), password)
}

export async function logout(): Promise<void> {
  await signOut(firebaseAuth)
}
