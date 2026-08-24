import { useState, type FormEvent, type ReactElement } from 'react'
import { login, loginWithGoogle, register } from '../infrastructure/firebase/auth'
import { describeAuthError } from '../infrastructure/firebase/authError'

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
        await login(email, password)
      } else {
        await register(email, password)
      }
    } catch (cause) {
      setError(describeAuthError(cause))
    } finally {
      setBusy(false)
    }
  }

  async function continueWithGoogle() {
    if (busy) return

    setBusy(true)
    setError('')

    try {
      await loginWithGoogle()
    } catch (cause) {
      setError(describeAuthError(cause))
      setBusy(false)
    }
  }

  return <main className="auth-shell"><section className="auth-card"><div className="brand-mark">WD</div><h1>Work_Disk Social</h1><p>Sign in with a real account to enter the Social Web.</p><button type="button" className="google-button" onClick={continueWithGoogle} disabled={busy}>Continue with Google</button><div className="auth-divider" aria-hidden="true"><span>or</span></div><form onSubmit={submit}><label>Email<input type="email" value={email} onChange={e => setEmail(e.target.value)} required autoComplete="email" /></label><label>Password<input type="password" value={password} onChange={e => setPassword(e.target.value)} required minLength={6} autoComplete={mode === 'login' ? 'current-password' : 'new-password'} /></label>{error && <div className="error" role="alert">{error}</div>}<button disabled={busy}>{busy ? 'Working…' : mode === 'login' ? 'Sign in' : 'Create account'}</button></form><button type="button" className="link-button" disabled={busy} onClick={() => { setError(''); setMode(mode === 'login' ? 'register' : 'login') }}>{mode === 'login' ? 'Create a new account' : 'I already have an account'}</button></section></main>
}
