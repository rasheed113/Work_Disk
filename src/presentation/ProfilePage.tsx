import { useEffect, useMemo, useState, type FormEvent, type ReactElement } from 'react'
import type { AuthenticatedIdentity } from '../social/domain/identity'
import type { Gender, SocialProfile } from '../social/domain/profile'
import { profileCompletion } from '../social/domain/profile'
import { FirebaseProfileRepository } from '../infrastructure/firebase/profileRepository'
import './profile.css'

const repository = new FirebaseProfileRepository()

export function ProfilePage({ identity }: { identity: AuthenticatedIdentity }): ReactElement {
  const [profile, setProfile] = useState<SocialProfile | null>(null)
  const [busy, setBusy] = useState(true)
  const [saving, setSaving] = useState(false)
  const [error, setError] = useState('')
  const [saved, setSaved] = useState(false)

  useEffect(() => {
    let active = true
    setBusy(true); setError('')
    void repository.getProfile(identity).then(value => { if (active) setProfile(value) }).catch(cause => { if (active) setError(cause instanceof Error ? cause.message : 'Profile could not be loaded') }).finally(() => { if (active) setBusy(false) })
    return () => { active = false }
  }, [identity])

  const completion = useMemo(() => profile ? profileCompletion(profile) : 0, [profile])

  function change(field: keyof SocialProfile, value: string) {
    setSaved(false)
    setProfile(current => current ? { ...current, [field]: field === 'age' ? (value ? Number(value) : null) : value } : current)
  }

  async function save(event: FormEvent) {
    event.preventDefault(); if (!profile) return
    setSaving(true); setError(''); setSaved(false)
    try { setProfile(await repository.saveProfile(identity, profile)); setSaved(true) }
    catch (cause) { setError(cause instanceof Error ? cause.message : 'Profile could not be saved') }
    finally { setSaving(false) }
  }

  if (busy) return <section className="profile-page"><div className="profile-panel profile-loading">Loading your real profile…</div></section>
  if (!profile) return <section className="profile-page"><div className="error banner">{error || 'Profile is unavailable.'}</div></section>

  return <section className="profile-page">
    <div className="profile-hero" style={profile.coverUrl ? { backgroundImage: `linear-gradient(180deg,rgba(4,12,8,.08),rgba(4,12,8,.92)),url(${profile.coverUrl})` } : undefined}><div className="profile-hero-content"><div className="profile-avatar-wrap"><div className="profile-avatar">{profile.photoUrl ? <img src={profile.photoUrl} alt="Profile" /> : profile.fullName.slice(0, 1).toUpperCase() || identity.email.slice(0, 1).toUpperCase()}</div></div><div><span className="eyebrow">SOCIAL PROFILE</span><h1>{profile.profileName || 'Complete your profile'}</h1><p>{profile.fullName || identity.email}</p></div></div></div>
    <div className="profile-completion profile-panel"><div><span className="eyebrow">PROFILE COMPLETION</span><strong>{completion}%</strong></div><div className="completion-track"><span style={{ width: `${completion}%` }} /></div><p>{completion === 100 ? 'Your required profile information is complete.' : 'Complete the highlighted profile details to finish your Social profile.'}</p></div>
    <form className="profile-panel profile-form" onSubmit={save}><div className="profile-section-heading"><span className="eyebrow">IDENTITY</span><h2>Profile details</h2></div><div className="profile-grid">
      <label>Profile name<input value={profile.profileName} onChange={event => change('profileName', event.target.value)} placeholder="Your public profile name" /></label>
      <label>Full name<input value={profile.fullName} onChange={event => change('fullName', event.target.value)} placeholder="Your full name" /></label>
      <label>Age<input type="number" min="1" max="120" value={profile.age ?? ''} onChange={event => change('age', event.target.value)} placeholder="Age" /></label>
      <label>Gender<select value={profile.gender} onChange={event => change('gender', event.target.value as Gender)}><option value="">Select gender</option><option value="female">Female</option><option value="male">Male</option><option value="non-binary">Non-binary</option><option value="prefer-not-to-say">Prefer not to say</option></select></label>
      <label>Mobile / contact number<input value={profile.mobile} onChange={event => change('mobile', event.target.value)} placeholder="Contact number" /></label>
      <label>Company name <span>(optional)</span><input value={profile.companyName} onChange={event => change('companyName', event.target.value)} placeholder="Company name" /></label>
      <label className="profile-wide">Profile photo URL<input value={profile.photoUrl} onChange={event => change('photoUrl', event.target.value)} placeholder="Authoritative image URL" /></label>
      <label className="profile-wide">Cover photo URL<input value={profile.coverUrl} onChange={event => change('coverUrl', event.target.value)} placeholder="Authoritative cover image URL" /></label>
    </div><div className="profile-system-card"><div><span className="eyebrow">WORK_DISK ID</span><strong>{profile.wdId}</strong><small>System-generated and immutable. Copy it for Social search or sending.</small></div><button type="button" className="profile-copy" onClick={() => void navigator.clipboard?.writeText(profile.wdId)}>Copy ID</button></div><label className="profile-email">Authenticated email<input value={identity.email} readOnly /></label>{error && <div className="error">{error}</div>}{saved && <div className="profile-saved">Profile saved successfully.</div>}<button className="profile-save" disabled={saving}>{saving ? 'Saving…' : 'Save profile'}</button></form>
  </section>
}
