import { useEffect, useMemo, useRef, useState, type ChangeEvent, type FormEvent, type ReactElement } from 'react'
import type { AuthenticatedIdentity } from '../social/domain/identity'
import type { Gender, SocialProfile } from '../social/domain/profile'
import { profileCompletion } from '../social/domain/profile'
import { FirebaseProfileRepository } from '../infrastructure/firebase/profileRepository'
import './profile.css'

const repository = new FirebaseProfileRepository()

type MediaTarget = 'profile' | 'cover'

export function ProfilePage({ identity }: { identity: AuthenticatedIdentity }): ReactElement {
  const [profile, setProfile] = useState<SocialProfile | null>(null)
  const [busy, setBusy] = useState(true)
  const [saving, setSaving] = useState(false)
  const [error, setError] = useState('')
  const [saved, setSaved] = useState(false)
  const [mediaTarget, setMediaTarget] = useState<MediaTarget | null>(null)
  const [previewUrl, setPreviewUrl] = useState('')
  const galleryRef = useRef<HTMLInputElement>(null)
  const cameraRef = useRef<HTMLInputElement>(null)

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

  function openMedia(target: MediaTarget, camera = false) {
    setMediaTarget(target)
    if (camera) cameraRef.current?.click()
    else galleryRef.current?.click()
  }

  function selectMedia(event: ChangeEvent<HTMLInputElement>) {
    const file = event.target.files?.[0]
    event.target.value = ''
    if (!file || !mediaTarget) return
    if (!file.type.startsWith('image/')) { setError('Please select an image file.'); return }
    if (previewUrl) URL.revokeObjectURL(previewUrl)
    setPreviewUrl(URL.createObjectURL(file))
  }

  function applyPreview() {
    if (!profile || !mediaTarget || !previewUrl) return
    setSaved(false)
    setProfile({ ...profile, [mediaTarget === 'profile' ? 'photoUrl' : 'coverUrl']: previewUrl })
    setPreviewUrl('')
    setMediaTarget(null)
  }

  function cancelPreview() {
    if (previewUrl) URL.revokeObjectURL(previewUrl)
    setPreviewUrl('')
    setMediaTarget(null)
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
    <input ref={galleryRef} className="media-input" type="file" accept="image/*" onChange={selectMedia} />
    <input ref={cameraRef} className="media-input" type="file" accept="image/*" capture="environment" onChange={selectMedia} />

    <div className="profile-hero" style={profile.coverUrl ? { backgroundImage: `linear-gradient(180deg,rgba(4,12,8,.08),rgba(4,12,8,.92)),url(${profile.coverUrl})` } : undefined}>
      <div className="profile-media-actions profile-cover-actions">
        <button type="button" onClick={() => openMedia('cover')} aria-label="Choose cover photo">🖼️ Gallery</button>
        <button type="button" onClick={() => openMedia('cover', true)} aria-label="Take cover photo">📷 Camera</button>
      </div>
      <div className="profile-hero-content">
        <div className="profile-avatar-wrap">
          <button type="button" className="profile-avatar profile-avatar-button" onClick={() => openMedia('profile')} aria-label="Choose profile photo">
            {profile.photoUrl ? <img src={profile.photoUrl} alt="Profile" /> : profile.fullName.slice(0, 1).toUpperCase() || identity.email.slice(0, 1).toUpperCase()}
            <span>🖼️</span>
          </button>
          <div className="avatar-camera"><button type="button" onClick={() => openMedia('profile', true)} aria-label="Take profile photo">📷</button></div>
        </div>
        <div><span className="eyebrow">SOCIAL PROFILE</span><h1>{profile.profileName || 'Complete your profile'}</h1><p>{profile.fullName || identity.email}</p></div>
      </div>
    </div>

    <div className="profile-completion profile-panel"><div><span className="eyebrow">PROFILE COMPLETION</span><strong>{completion}%</strong></div><div className="completion-track"><span style={{ width: `${completion}%` }} /></div><p>{completion === 100 ? 'Your required profile information is complete.' : 'Complete the highlighted profile details to finish your Social profile.'}</p></div>

    <form className="profile-panel profile-form" onSubmit={save}>
      <div className="profile-section-heading"><span className="eyebrow">EDIT PROFILE</span><h2>Profile details</h2></div>
      <div className="profile-grid">
        <label>Profile name<input value={profile.profileName} onChange={event => change('profileName', event.target.value)} placeholder="Your public profile name" /></label>
        <label>Full name<input value={profile.fullName} onChange={event => change('fullName', event.target.value)} placeholder="Your full name" /></label>
        <label>Age<input type="number" min="1" max="120" value={profile.age ?? ''} onChange={event => change('age', event.target.value)} placeholder="Age" /></label>
        <label>Gender<select value={profile.gender} onChange={event => change('gender', event.target.value as Gender)}><option value="">Select gender</option><option value="female">Female</option><option value="male">Male</option><option value="non-binary">Non-binary</option><option value="prefer-not-to-say">Prefer not to say</option></select></label>
        <label>Mobile / contact number<input value={profile.mobile} onChange={event => change('mobile', event.target.value)} placeholder="Contact number" /></label>
        <label>Company name <span>(optional)</span><input value={profile.companyName} onChange={event => change('companyName', event.target.value)} placeholder="Company name" /></label>
      </div>
      <div className="profile-system-card"><div><span className="eyebrow">WORK_DISK ID</span><strong>{profile.wdId}</strong><small>System-generated and immutable. Copy it for Social search or sending.</small></div><button type="button" className="profile-copy" onClick={() => void navigator.clipboard?.writeText(profile.wdId)}>Copy ID</button></div>
      <label className="profile-email">Authenticated email<input value={identity.email} readOnly /></label>
      {error && <div className="error">{error}</div>}{saved && <div className="profile-saved">Profile saved successfully.</div>}
      <button className="profile-save" disabled={saving}>{saving ? 'Saving…' : 'Save profile'}</button>
    </form>

    {mediaTarget && previewUrl && <div className="media-editor-backdrop" role="dialog" aria-modal="true"><div className={`media-editor ${mediaTarget === 'cover' ? 'cover-editor' : ''}`}><span className="eyebrow">ADJUST {mediaTarget === 'profile' ? 'PROFILE PHOTO' : 'COVER PHOTO'}</span><h2>Preview & adjust</h2><div className="media-preview"><img src={previewUrl} alt="Selected preview" /></div><div className="media-editor-actions"><button type="button" onClick={cancelPreview}>Cancel</button><button type="button" onClick={() => openMedia(mediaTarget)}>Choose another</button><button type="button" className="profile-save" onClick={applyPreview}>Use photo</button></div></div></div>}
  </section>
}
