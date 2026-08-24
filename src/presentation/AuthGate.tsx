import { useState, type FormEvent, type ReactElement } from 'react'
import { login, register } from '../infrastructure/firebase/auth'
import { describeAuthError } from '../infrastructure/firebase/authError'

const AUTH_TIMEOUT_MS = 15_000

async function withAuthTimeout<T>(operation: Promise<T>): Promise<T> {
  let timeoutId: ReturnType<typeof setTimeout> | undefined
  const timeout = new Promise<T>((_, reject) => {
    timeoutId = setTimeout(() => {
      reject(new Error('Firebase authentication timed out after 15 seconds. Please check the live site connection to Firebase and try again.'))
    }, AUTH_TIMEOUT_MS)
  })

  try {
    return await Promise.race([operation, timeout])
  } finally {
    if (timeoutId !== undefined) clearTimeout(timeoutId)
  }
}

export function AuthGate(): ReactElement {
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const [mode, setMode] = useState<'login' | 'register'>('login')
  const [busy, setBusy] = useState(false)
  const [error, setError] = useState('')

  async function submit(event: FormEvent) {
    event.preventDefault()
    if (busy) return

    setBusy(true)
    setError('')

    try {
      if (mode === 'login') {
        await withAuthTimeout(login(email, password))
      } else {
        await withAuthTimeout(register(email, password))
      }
    } catch (cause) {
      setError(describeAuthError(cause))
    } finally {
      setBusy(false)
    }
  }

  return <main className="auth-shell"><section className="auth-card"><div className="brand-mark">WD</div><h1>Work_Disk Social</h1><p>Sign in with a real account to enter the Social Web.</p><form onSubmit={submit}><label>Email<input type="email" value={email} onChange={e => setEmail(e.target.value)} required autoComplete="email" /></label><label>Password<input type="password" value={password} onChange={e => setPassword(e.target.value)} required minLength={6} autoComplete={mode === 'login' ? 'current-password' : 'new-password'} /></label>{error && <div className="error" role="alert">{error}</div>}<button disabled={busy}>{busy ? 'Working…' : mode === 'login' ? 'Sign in' : 'Create account'}</button></form><button className="link-button" onClick={() => { setError(''); setMode(mode === 'login' ? 'register' : 'login') }}>{mode === 'login' ? 'Create a new account' : 'I already have an account'}</button></section></main>
}
