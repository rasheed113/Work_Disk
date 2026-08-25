import { useState, type FormEvent, type ReactElement } from 'react'
import { login, loginWithGoogle, register, resetPassword } from '../infrastructure/firebase/auth'
import { describeAuthError } from '../infrastructure/firebase/authError'

type AuthGateProps = { onAuthenticated?: never }

export function AuthGate(_props: AuthGateProps): ReactElement {
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const [mode, setMode] = useState<'login' | 'register'>('login')
  const [busy, setBusy] = useState(false)
  const [error, setError] = useState('')
  const [resetOpen, setResetOpen] = useState(false)
  const [resetEmail, setResetEmail] = useState('')
  const [resetSent, setResetSent] = useState(false)
  const [ripples, setRipples] = useState<Array<{ id: number; x: number; y: number }>>([])

  function createRipple(event: React.PointerEvent<HTMLElement>) {
    if (event.pointerType === 'mouse' && event.button !== 0) return
    const id = Date.now() + Math.random()
    setRipples(current => [...current, { id, x: event.clientX, y: event.clientY }])
    window.setTimeout(() => setRipples(current => current.filter(ripple => ripple.id !== id)), 900)
  }

  async function submit(event: FormEvent) {
    event.preventDefault()
    if (busy) return
    setBusy(true); setError('')
    try { if (mode === 'login') await login(email, password); else await register(email, password) }
    catch (cause) { setError(describeAuthError(cause)) }
    finally { setBusy(false) }
  }

  function openPasswordReset() { if (busy) return; setError(''); setResetSent(false); setResetEmail(email); setResetOpen(true) }
  function closePasswordReset() { if (busy) return; setResetOpen(false); setResetSent(false) }

  async function sendResetEmail() {
    if (busy) return
    setBusy(true); setError(''); setResetSent(false)
    try { await resetPassword(resetEmail); setResetSent(true) }
    catch (cause) { setError(describeAuthError(cause)) }
    finally { setBusy(false) }
  }

  async function continueWithGoogle() {
    if (busy) return
    setBusy(true); setError('')
    try {
      await loginWithGoogle()
      // Firebase onAuthStateChanged is the single authoritative identity boundary.
      // Do not construct or push a second identity from the popup credential here.
    } catch (cause) { setError(describeAuthError(cause)) }
    finally { setBusy(false) }
  }

  return <main className="auth-shell" onPointerDown={createRipple}><div className="auth-ripple-layer" aria-hidden="true">{ripples.map(ripple => <span key={ripple.id} className="auth-ripple" style={{ left: ripple.x, top: ripple.y }} />)}</div><section className="auth-card"><div className="brand-mark">WD</div><h1>Work_Disk Social</h1><p>Sign in with a real account to enter the Social Web.</p><button type="button" className="google-button" onClick={continueWithGoogle} disabled={busy}><span className="google-icon" aria-hidden="true">G</span><span>Continue with Google</span></button><div className="auth-divider" aria-hidden="true"><span>or</span></div><form onSubmit={submit}><label>Email<input type="email" value={email} onChange={e => setEmail(e.target.value)} required autoComplete="email" /></label><label>Password<input type="password" value={password} onChange={e => setPassword(e.target.value)} required minLength={6} autoComplete={mode === 'login' ? 'current-password' : 'new-password'} /></label>{error && <div className="error" role="alert">{error}</div>}<button disabled={busy}>{busy ? 'Working…' : mode === 'login' ? 'Sign in' : 'Create account'}</button></form>{mode === 'login' && <button type="button" className="link-button" disabled={busy} onClick={openPasswordReset}>Forgot password?</button>}<button type="button" className="link-button" disabled={busy} onClick={() => { setError(''); setMode(mode === 'login' ? 'register' : 'login') }}>{mode === 'login' ? 'Create a new account' : 'I already have an account'}</button></section>{resetOpen && <div className="auth-modal-backdrop" role="presentation"><section className="auth-modal" role="dialog" aria-modal="true" aria-labelledby="password-reset-title"><h2 id="password-reset-title">Reset your password</h2>{resetSent ? <><p className="reset-success"><strong>Password reset email sent.</strong><span>Check your inbox for the password reset link. If you don't see it, please check your Spam/Junk folder too.</span></p><button type="button" onClick={closePasswordReset}>Close</button></> : <><label>Email<input type="email" value={resetEmail} onChange={e => setResetEmail(e.target.value)} autoComplete="email" autoFocus /></label>{error && <div className="error" role="alert">{error}</div>}<button type="button" disabled={busy} onClick={sendResetEmail}>{busy ? 'Sending…' : 'Send reset email'}</button><button type="button" className="link-button" disabled={busy} onClick={closePasswordReset}>Cancel</button></>}</section></div>}</main>
}
