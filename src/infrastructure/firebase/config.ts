import { initializeApp, type FirebaseOptions } from 'firebase/app'
import { browserLocalPersistence, getAuth, setPersistence } from 'firebase/auth'
import { getFirestore } from 'firebase/firestore'

const config: FirebaseOptions = {
  apiKey: import.meta.env.VITE_FIREBASE_API_KEY,
  authDomain: import.meta.env.VITE_FIREBASE_AUTH_DOMAIN,
  projectId: import.meta.env.VITE_FIREBASE_PROJECT_ID,
  storageBucket: import.meta.env.VITE_FIREBASE_STORAGE_BUCKET,
  messagingSenderId: import.meta.env.VITE_FIREBASE_MESSAGING_SENDER_ID,
  appId: import.meta.env.VITE_FIREBASE_APP_ID,
}

for (const [name, value] of Object.entries(config)) {
  if (!value) throw new Error(`Missing Firebase web configuration: ${name}`)
}

const app = initializeApp(config)
export const firebaseAuth = getAuth(app)
export const firebaseAuthReady = setPersistence(firebaseAuth, browserLocalPersistence)
export const firestore = getFirestore(app)
