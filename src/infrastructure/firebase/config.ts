import { initializeApp, type FirebaseOptions } from 'firebase/app'
import { getAuth } from 'firebase/auth'
import { getFirestore } from 'firebase/firestore'

function required(name: string): string {
  const value = import.meta.env[name] as string | undefined
  if (!value) throw new Error(`Missing Firebase web configuration: ${name}`)
  return value
}

const config: FirebaseOptions = {
  apiKey: required('VITE_FIREBASE_API_KEY'),
  authDomain: required('VITE_FIREBASE_AUTH_DOMAIN'),
  projectId: required('VITE_FIREBASE_PROJECT_ID'),
  storageBucket: required('VITE_FIREBASE_STORAGE_BUCKET'),
  messagingSenderId: required('VITE_FIREBASE_MESSAGING_SENDER_ID'),
  appId: required('VITE_FIREBASE_APP_ID'),
}

const app = initializeApp(config)
export const firebaseAuth = getAuth(app)
export const firestore = getFirestore(app)
