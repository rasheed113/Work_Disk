import { useEffect, useMemo, useRef, useState, type ChangeEvent, type FormEvent, type ReactElement } from 'react'
import type { AuthenticatedIdentity } from '../social/domain/identity'
import type { Gender, SocialProfile } from '../social/domain/profile'
import { profileCompletion } from '../social/domain/profile'
import { FirebaseProfileRepository } from '../infrastructure/firebase/profileRepository'
import './profile.css'

const repository = new FirebaseProfileRepository()
type MediaTarget = 'profile' | 'cover'
type CropState = { zoom: number; x: number; y: number }
const DEFAULT_CROP: CropState = { zoom: 1, x: 0, y: 0 }

async function imageDataUrl(file: File, target: MediaTarget, crop: CropState): Promise<string> {
  const source = URL.createObjectURL(file)
  try {
    const image = new Image(); image.src = source
    await new Promise<void>((resolve, reject) => { image.onload = () => resolve(); image.onerror = () => reject(new Error('The selected image could not be read.')) })
    const outputW = target === 'profile' ? 640 : 1200
    const outputH = target === 'profile' ? 640 : 675
    const canvas = document.createElement('canvas'); canvas.width = outputW; canvas.height = outputH
    const context = canvas.getContext('2d'); if (!context) throw new Error('Image editor is unavailable in this browser.')
    const targetAspect = outputW / outputH; const sourceAspect = image.naturalWidth / image.naturalHeight
    let drawW: number, drawH: number
    if (sourceAspect > targetAspect) { drawH = outputH * crop.zoom; drawW = drawH * sourceAspect } else { drawW = outputW * crop.zoom; drawH = drawW / sourceAspect }
    const maxX = Math.max(0, (drawW - outputW) / 2); const maxY = Math.max(0, (drawH - outputH) / 2)
    const offsetX = crop.x * maxX; const offsetY = crop.y * maxY
    context.fillStyle = '#000'; context.fillRect(0, 0, outputW, outputH)
    context.drawImage(image, (outputW - drawW) / 2 + offsetX, (outputH - drawH) / 2 + offsetY, drawW, drawH)
    return canvas.toDataURL('image/jpeg', 0.82)
  } finally { URL.revokeObjectURL(source) }
}

export function ProfilePage({ identity }: { identity: AuthenticatedIdentity }): ReactElement {
  const [profile, setProfile] = useState<SocialProfile | null>(null)
  const [busy, setBusy] = useState(true); const [saving, setSaving] = useState(false); const [mediaSaving, setMediaSaving] = useState(false)
  const [error, setError] = useState(''); const [saved, setSaved] = useState(false); const [editingMedia, setEditingMedia] = useState(false)
  const [mediaTarget, setMediaTarget] = useState<MediaTarget>('profile'); const [selectedFile, setSelectedFile] = useState<File | null>(null); const [previewUrl, setPreviewUrl] = useState(''); const [crop, setCrop] = useState<CropState>(DEFAULT_CROP)
  const galleryRef = useRef<HTMLInputElement>(null); const cameraRef = useRef<HTMLInputElement>(null)

  useEffect(() => { let active = true; setBusy(true); setError(''); void repository.getProfile(identity).then(value => { if (active) setProfile(value) }).catch(cause => { if (active) setError(cause instanceof Error ? cause.message : 'Profile could not be loaded') }).finally(() => { if (active) setBusy(false) }); return () => { active = false } }, [identity])
  const completion = useMemo(() => profile ? profileCompletion(profile) : 0, [profile])
  function change(field: keyof SocialProfile, value: string) { setSaved(false); setProfile(current => current ? { ...current, [field]: field === 'age' ? (value ? Number(value) : null) : value } : current) }
  function choose(target: MediaTarget, camera: boolean) { setMediaTarget(target); if (camera) cameraRef.current?.click(); else galleryRef.current?.click() }
  async function selectMedia(event: ChangeEvent<HTMLInputElement>) { const file = event.target.files?.[0]; event.target.value = ''; if (!file) return; if (!file.type.startsWith('image/')) { setError('Please select an image file.'); return }; setError(''); setSelectedFile(file); setCrop(DEFAULT_CROP); setPreviewUrl(URL.createObjectURL(file)); setEditingMedia(false) }
  async function applyPreview() { if (!profile || !selectedFile) return; setMediaSaving(true); setError(''); setSaved(false); try { const dataUrl = await imageDataUrl(selectedFile, mediaTarget, crop); const next = { ...profile, [mediaTarget === 'profile' ? 'photoUrl' : 'coverUrl']: dataUrl }; const persisted = await repository.saveProfile(identity, next); setProfile(persisted); closeMediaEditor(); setSaved(true) } catch (cause) { setError(cause instanceof Error ? cause.message : 'Photo could not be saved.') } finally { setMediaSaving(false) } }
  function closeMediaEditor() { if (previewUrl) URL.revokeObjectURL(previewUrl); setPreviewUrl(''); setSelectedFile(null); setCrop(DEFAULT_CROP); setEditingMedia(false) }
  function move(axis: 'x' | 'y', amount: number) { setCrop(current => ({ ...current, [axis]: Math.max(-1, Math.min(1, current[axis] + amount)) })) }
  async function save(event: FormEvent) { event.preventDefault(); if (!profile) return; setSaving(true); setError(''); setSaved(false); try { setProfile(await repository.saveProfile(identity, profile)); setSaved(true) } catch (cause) { setError(cause instanceof Error ? cause.message : 'Profile could not be saved') } finally { setSaving(false) } }
  if (busy) return <section className="profile-page"><div className="profile-panel profile-loading">Loading your real profile…</div></section>
  if (!profile) return <section className="profile-page"><div className="error banner">{error || 'Profile is unavailable.'}</div></section>

  return <section className="profile-page">
    <input ref={galleryRef} className="media-input" type="file" accept="image/*" onChange={selectMedia} /><input ref={cameraRef} className="media-input" type="file" accept="image/*" capture="environment" onChange={selectMedia} />
    <div className="profile-hero" style={profile.coverUrl ? { backgroundImage: `linear-gradient(180deg,rgba(4,12,8,.08),rgba(4,12,8,.92)),url(${profile.coverUrl})` } : undefined}>
      <button type="button" className="media-edit-button" onClick={() => { setMediaTarget('cover'); setEditingMedia(value => !value) }} aria-label="Edit cover photo">✎</button>
      {editingMedia && mediaTarget === 'cover' && <div className="media-edit-menu"><button type="button" onClick={() => choose('cover', false)}>🖼️ Gallery</button><button type="button" onClick={() => choose('cover', true)}>📷 Camera</button></div>}
      <div className="profile-hero-content"><div className="profile-avatar-wrap"><div className="profile-avatar">{profile.photoUrl ? <img src={profile.photoUrl} alt="Profile" /> : profile.fullName.slice(0, 1).toUpperCase() || identity.email.slice(0, 1).toUpperCase()}</div><button type="button" className="avatar-edit-button" onClick={() => { setMediaTarget('profile'); setEditingMedia(value => !value) }} aria-label="Edit profile photo">✎</button>{editingMedia && mediaTarget === 'profile' && <div className="media-edit-menu avatar-menu"><button type="button" onClick={() => choose('profile', false)}>🖼️ Gallery</button><button type="button" onClick={() => choose('profile', true)}>📷 Camera</button></div>}</div><div><span className="eyebrow">SOCIAL PROFILE</span><h1>{profile.profileName || 'Complete your profile'}</h1><p>{profile.fullName || identity.email}</p></div></div>
    </div>
    {previewUrl && <div className="media-editor-backdrop" role="dialog" aria-modal="true"><div className={`media-editor ${mediaTarget === 'cover' ? 'cover-editor' : ''}`}><span className="eyebrow">ADJUST {mediaTarget === 'profile' ? 'PROFILE PHOTO' : 'COVER PHOTO'}</span><h2>Crop & position</h2><div className="media-preview crop-preview"><img src={previewUrl} alt="Selected preview" /></div><div className="crop-controls"><label>Zoom <input type="range" min="1" max="2.5" step=".01" value={crop.zoom} onChange={event => setCrop(current => ({ ...current, zoom: Number(event.target.value) }))} /></label><div className="crop-direction"><button type="button" onClick={() => move('x', -.1)}>←</button><button type="button" onClick={() => move('y', -.1)}>↑</button><button type="button" onClick={() => setCrop(DEFAULT_CROP)}>↺ Reset</button><button type="button" onClick={() => move('y', .1)}>↓</button><button type="button" onClick={() => move('x', .1)}>→</button></div></div><div className="media-editor-actions"><button type="button" onClick={closeMediaEditor}>Cancel</button><button type="button" onClick={() => choose(mediaTarget, false)} disabled={mediaSaving}>Choose another</button><button type="button" className="profile-save" onClick={() => void applyPreview()} disabled={mediaSaving}>{mediaSaving ? 'Saving…' : 'Use photo'}</button></div></div></div>}
    <div className="profile-completion profile-panel"><div><span className="eyebrow">PROFILE COMPLETION</span><strong>{completion}%</strong></div><div className="completion-track"><span style={{ width: `${completion}%` }} /></div><p>{completion === 100 ? 'Your required profile information is complete.' : 'Complete the highlighted profile details to finish your Social profile.'}</p></div>
    <form className="profile-panel profile-form" onSubmit={save}><div className="profile-section-heading"><span className="eyebrow">EDIT PROFILE</span><h2>Profile details</h2></div><div className="profile-grid"><label>Profile name<input value={profile.profileName} onChange={event => change('profileName', event.target.value)} placeholder="Your public profile name" /></label><label>Full name<input value={profile.fullName} onChange={event => change('fullName', event.target.value)} placeholder="Your full name" /></label><label>Age<input type="number" min="1" max="120" value={profile.age ?? ''} onChange={event => change('age', event.target.value)} placeholder="Age" /></label><label>Gender<select value={profile.gender} onChange={event => change('gender', event.target.value as Gender)}><option value="">Select gender</option><option value="female">Female</option><option value="male">Male</option><option value="non-binary">Non-binary</option><option value="prefer-not-to-say">Prefer not to say</option></select></label><label>Mobile / contact number<input value={profile.mobile} onChange={event => change('mobile', event.target.value)} placeholder="Contact number" /></label><label>Company name <span>(optional)</span><input value={profile.companyName} onChange={event => change('companyName', event.target.value)} placeholder="Company name" /></label></div><div className="profile-system-card"><div><span className="eyebrow">WORK_DISK ID</span><strong>{profile.wdId}</strong><small>System-generated and immutable. Copy it for Social search or sending.</small></div><button type="button" className="profile-copy" onClick={() => void navigator.clipboard?.writeText(profile.wdId)}>Copy ID</button></div><label className="profile-email">Authenticated email<input value={identity.email} readOnly /></label>{error && <div className="error">{error}</div>}{saved && <div className="profile-saved">Profile saved successfully.</div>}<button className="profile-save" disabled={saving}>{saving ? 'Saving…' : 'Save profile'}</button></form>
  </section>
}
