import { useState, type FormEvent, type ReactElement } from 'react'
import { login, loginWithGoogle, register, resetPassword } from '../infrastructure/firebase/auth'
import { describeAuthError } from '../infrastructure/firebase/authError'

export function AuthGate(): ReactElement {
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const [mode, setMode] = useState<'login' | 'register'>('login')
  const [busy, setBusy] = useState(false)
  const [error, setError] = useState('')
  const [resetSent, setResetSent] = useState(false)

  async function submit(event: FormEvent) {
    event.preventDefault()
    if (busy) return
    setBusy(true)
    setError('')
    setResetSent(false)
    try {
      if (mode === 'login') await login(email, password)
      else await register(email, password)
    } catch (cause) {
      setError(describeAuthError(cause))
    } finally {
      setBusy(false)
    }
  }

  async function forgotPassword() {
    if (busy) return
    setBusy(true)
    setError('')
    setResetSent(false)
    try {
      await resetPassword(email)
      setResetSent(true)
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
    setResetSent(false)
    try {
      await loginWithGoogle()
    } catch (cause) {
      setError(describeAuthError(cause))
    } finally {
      setBusy(false)
    }
  }

  return <main className="auth-shell"><section className="auth-card"><div className="brand-mark">WD</div><h1>Work_Disk Social</h1><p>Sign in with a real account to enter the Social Web.</p><button type="button" className="google-button" onClick={continueWithGoogle} disabled={busy}>Continue with Google</button><div className="auth-divider" aria-hidden="true"><span>or</span></div><form onSubmit={submit}><label>Email<input type="email" value={email} onChange={e => setEmail(e.target.value)} required autoComplete="email" /></label><label>Password<input type="password" value={password} onChange={e => setPassword(e.target.value)} required minLength={6} autoComplete={mode === 'login' ? 'current-password' : 'new-password'} /></label>{error && <div className="error" role="alert">{error}</div>}{resetSent && <div className="success" role="status">Password reset email sent. Check your inbox.</div>}<button disabled={busy}>{busy ? 'Working…' : mode === 'login' ? 'Sign in' : 'Create account'}</button></form>{mode === 'login' && <button type="button" className="link-button" disabled={busy} onClick={forgotPassword}>Forgot password?</button>}<button type="button" className="link-button" disabled={busy} onClick={() => { setError(''); setResetSent(false); setMode(mode === 'login' ? 'register' : 'login') }}>{mode === 'login' ? 'Create a new account' : 'I already have an account'}</button></section></main>
}
