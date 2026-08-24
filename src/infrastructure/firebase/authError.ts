import { FirebaseError } from 'firebase/app'

export function describeAuthError(cause: unknown): string {
  if (cause instanceof FirebaseError) {
    const messages: Record<string, string> = {
      'auth/email-already-in-use': 'This email already has a Work_Disk account. Use Sign in instead.',
      'auth/invalid-email': 'Please enter a valid email address.',
      'auth/weak-password': 'Password must be at least 6 characters.',
      'auth/invalid-credential': 'The email or password is incorrect.',
      'auth/user-not-found': 'No Work_Disk account exists for this email.',
      'auth/wrong-password': 'The email or password is incorrect.',
      'auth/operation-not-allowed': 'Email/password authentication is not enabled in Firebase.',
      'auth/api-key-not-valid.-please-pass-a-valid-api-key.': 'Firebase API key is invalid for this Web App.',
      'auth/network-request-failed': 'Firebase could not reach the authentication service. Check the internet connection and try again.',
    }
    return messages[cause.code] ?? `Firebase authentication failed (${cause.code}).`
  }

  if (cause instanceof Error) return cause.message
  return 'Authentication failed.'
}
