import { useEffect, useState, type ReactElement } from 'react'
import { confirmPasswordReset, verifyPasswordResetCode } from 'firebase/auth'
import { firebaseAuth } from '../infrastructure/firebase/config'
import { describeAuthError } from '../infrastructure/firebase/authError'

export function PasswordResetPage(): ReactElement {
  const params = new URLSearchParams(window.location.search)
  const mode = params.get('mode')
  const oobCode = params.get('oobCode')
  const [email, setEmail] = useState('')
  const [password, setPassword] = useState('')
  const [confirmPassword, setConfirmPassword] = useState('')
  const [busy, setBusy] = useState(Boolean(oobCode))
  const [ready, setReady] = useState(false)
  const [done, setDone] = useState(false)
  const [error, setError] = useState('')

  useEffect(() => {
    if (mode !== 'resetPassword' || !oobCode) return
    const resetCode = oobCode
    verifyPasswordResetCode(firebaseAuth, resetCode)
      .then(accountEmail => { setEmail(accountEmail); setReady(true) })
      .catch(cause => setError(describeAuthError(cause)))
      .finally(() => setBusy(false))
  }, [mode, oobCode])

  if (mode !== 'resetPassword' || !oobCode) {
    return <main className="auth-shell"><section className="auth-card"><div className="brand-mark">WD</div><h1>Invalid password reset link</h1><p>This password reset link is missing or invalid. Request a new reset email from Work_Disk.</p><button type="button" onClick={() => { window.location.href = '/' }}>Back to sign in</button></section></main>
  }

  async function submit() {
    if (busy || !ready) return
    if (password.length < 6) { setError('Password must be at least 6 characters.'); return }
    if (password !== confirmPassword) { setError('Passwords do not match.'); return }
    setBusy(true); setError('')
    const resetCode = oobCode
    try { await confirmPasswordReset(firebaseAuth, resetCode, password); setDone(true) }
    catch (cause) { setError(describeAuthError(cause)) }
    finally { setBusy(false) }
  }

  return <main className="auth-shell"><section className="auth-card"><div className="brand-mark">WD</div><h1>Reset your password</h1>{done ? <><p>Your password has been changed successfully.</p><button type="button" onClick={() => { window.location.href = '/' }}>Sign in</button></> : <><p>{email}</p>{error && <div className="error" role="alert">{error}</div>}<label>Password<input type="password" value={password} onChange={e => setPassword(e.target.value)} autoComplete="new-password" disabled={!ready || busy} /></label><label>Confirm password<input type="password" value={confirmPassword} onChange={e => setConfirmPassword(e.target.value)} autoComplete="new-password" disabled={!ready || busy} /></label><button type="button" onClick={submit} disabled={!ready || busy}>{busy ? 'Working…' : 'Set new password'}</button></>}</section></main>
}
