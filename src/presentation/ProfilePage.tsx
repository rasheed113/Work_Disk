import { useEffect, useMemo, useRef, useState, type ChangeEvent, type FormEvent, type ReactElement } from 'react'
import type { AuthenticatedIdentity } from '../social/domain/identity'
import type { Gender, SocialProfile } from '../social/domain/profile'
import { profileCompletion } from '../social/domain/profile'
import { FirebaseProfileRepository } from '../infrastructure/firebase/profileRepository'
import './profile.css'

const repository = new FirebaseProfileRepository()
type MediaTarget = 'profile' | 'cover'
type CropState = { zoom: number; x: number; y: number }
type Point = { x: number; y: number }
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
    context.fillStyle = '#000'; context.fillRect(0, 0, outputW, outputH)
    context.drawImage(image, (outputW - drawW) / 2 + crop.x * maxX, (outputH - drawH) / 2 + crop.y * maxY, drawW, drawH)
    return canvas.toDataURL('image/jpeg', 0.82)
  } finally { URL.revokeObjectURL(source) }
}

export function ProfilePage({ identity }: { identity: AuthenticatedIdentity }): ReactElement {
  const [profile, setProfile] = useState<SocialProfile | null>(null)
  const [busy, setBusy] = useState(true); const [saving, setSaving] = useState(false); const [mediaSaving, setMediaSaving] = useState(false)
  const [error, setError] = useState(''); const [saved, setSaved] = useState(false); const [editProfile, setEditProfile] = useState(false)
  const [editingMedia, setEditingMedia] = useState(false); const [mediaTarget, setMediaTarget] = useState<MediaTarget>('profile')
  const [selectedFile, setSelectedFile] = useState<File | null>(null); const [previewUrl, setPreviewUrl] = useState(''); const [crop, setCrop] = useState<CropState>(DEFAULT_CROP)
  const galleryRef = useRef<HTMLInputElement>(null); const cameraRef = useRef<HTMLInputElement>(null)
  const gestureRef = useRef<{ pointers: Map<number, Point>; startCrop: CropState; startDistance: number; startCenter: Point; startZoom: number }>({ pointers: new Map(), startCrop: DEFAULT_CROP, startDistance: 0, startCenter: { x: 0, y: 0 }, startZoom: 1 })

  useEffect(() => { let active = true; setBusy(true); setError(''); void repository.getProfile(identity).then(value => { if (active) setProfile(value) }).catch(cause => { if (active) setError(cause instanceof Error ? cause.message : 'Profile could not be loaded') }).finally(() => { if (active) setBusy(false) }); return () => { active = false } }, [identity])
  const completion = useMemo(() => profile ? profileCompletion(profile) : 0, [profile])
  function change(field: keyof SocialProfile, value: string) { setSaved(false); setProfile(current => current ? { ...current, [field]: field === 'age' ? (value ? Number(value) : null) : value } : current) }
  function choose(target: MediaTarget, camera: boolean) { setMediaTarget(target); if (camera) cameraRef.current?.click(); else galleryRef.current?.click() }
  function selectMedia(event: ChangeEvent<HTMLInputElement>) { const file = event.target.files?.[0]; event.target.value = ''; if (!file) return; if (!file.type.startsWith('image/')) { setError('Please select an image file.'); return }; setError(''); setSelectedFile(file); setCrop(DEFAULT_CROP); setPreviewUrl(URL.createObjectURL(file)); setEditingMedia(false) }
  function points() { return [...gestureRef.current.pointers.values()] }
  function distance(a: Point, b: Point) { return Math.hypot(a.x - b.x, a.y - b.y) }
  function center(a: Point, b: Point): Point { return { x: (a.x + b.x) / 2, y: (a.y + b.y) / 2 } }
  function onPointerDown(event: React.PointerEvent<HTMLDivElement>) { event.currentTarget.setPointerCapture(event.pointerId); const g = gestureRef.current; g.pointers.set(event.pointerId, { x: event.clientX, y: event.clientY }); const pts = points(); g.startCrop = crop; if (pts.length === 1) g.startCenter = pts[0]; if (pts.length === 2) { g.startDistance = distance(pts[0], pts[1]); g.startCenter = center(pts[0], pts[1]); g.startZoom = crop.zoom } }
  function onPointerMove(event: React.PointerEvent<HTMLDivElement>) { const g = gestureRef.current; if (!g.pointers.has(event.pointerId)) return; g.pointers.set(event.pointerId, { x: event.clientX, y: event.clientY }); const pts = points(); if (pts.length === 1) { const dx = (pts[0].x - g.startCenter.x) / 150; const dy = (pts[0].y - g.startCenter.y) / 150; setCrop({ ...g.startCrop, x: Math.max(-1, Math.min(1, g.startCrop.x + dx)), y: Math.max(-1, Math.min(1, g.startCrop.y + dy)) }) } else if (pts.length === 2) { const nextDistance = distance(pts[0], pts[1]); const nextCenter = center(pts[0], pts[1]); const zoom = Math.max(1, Math.min(2.8, g.startZoom * (nextDistance / Math.max(1, g.startDistance)))); const dx = (nextCenter.x - g.startCenter.x) / 150; const dy = (nextCenter.y - g.startCenter.y) / 150; setCrop({ zoom, x: Math.max(-1, Math.min(1, g.startCrop.x + dx)), y: Math.max(-1, Math.min(1, g.startCrop.y + dy)) }) } }
  function onPointerUp(event: React.PointerEvent<HTMLDivElement>) { gestureRef.current.pointers.delete(event.pointerId) }
  function onWheel(event: React.WheelEvent<HTMLDivElement>) { event.preventDefault(); setCrop(current => ({ ...current, zoom: Math.max(1, Math.min(2.8, current.zoom * (event.deltaY > 0 ? 0.94 : 1.06))) })) }
  async function applyPreview() { if (!profile || !selectedFile) return; setMediaSaving(true); setError(''); setSaved(false); try { const dataUrl = await imageDataUrl(selectedFile, mediaTarget, crop); const next = { ...profile, [mediaTarget === 'profile' ? 'photoUrl' : 'coverUrl']: dataUrl }; const persisted = await repository.saveProfile(identity, next); setProfile(persisted); closeMediaEditor(); setSaved(true) } catch (cause) { setError(cause instanceof Error ? cause.message : 'Photo could not be saved.') } finally { setMediaSaving(false) } }
  function closeMediaEditor() { if (previewUrl) URL.revokeObjectURL(previewUrl); setPreviewUrl(''); setSelectedFile(null); setCrop(DEFAULT_CROP); setEditingMedia(false) }
  async function save(event: FormEvent) { event.preventDefault(); if (!profile) return; setSaving(true); setError(''); setSaved(false); try { setProfile(await repository.saveProfile(identity, profile)); setSaved(true); setEditProfile(false) } catch (cause) { setError(cause instanceof Error ? cause.message : 'Profile could not be saved') } finally { setSaving(false) } }
  if (busy) return <section className="profile-page"><div className="profile-panel profile-loading">Loading your real profile…</div></section>
  if (!profile) return <section className="profile-page"><div className="error banner">{error || 'Profile is unavailable.'}</div></section>

  return <section className="profile-page">
    <input ref={galleryRef} className="media-input" type="file" accept="image/*" onChange={selectMedia} /><input ref={cameraRef} className="media-input" type="file" accept="image/*" capture="environment" onChange={selectMedia} />
    <div className="profile-cover" style={profile.coverUrl ? { backgroundImage: `linear-gradient(180deg,rgba(4,12,8,.02),rgba(4,12,8,.82)),url(${profile.coverUrl})` } : undefined}>
      <button type="button" className="media-edit-button cover-edit-button" onClick={() => { setMediaTarget('cover'); setEditingMedia(value => !value) }} aria-label="Edit cover photo">✎</button>
      {editingMedia && mediaTarget === 'cover' && <div className="media-edit-menu cover-menu"><button type="button" onClick={() => choose('cover', false)}>🖼️ Gallery</button><button type="button" onClick={() => choose('cover', true)}>📷 Camera</button></div>}
    </div>
    <div className="profile-identity-row"><div className="profile-avatar-wrap"><div className="profile-avatar">{profile.photoUrl ? <img src={profile.photoUrl} alt="Profile" /> : profile.fullName.slice(0, 1).toUpperCase() || identity.email.slice(0, 1).toUpperCase()}</div><button type="button" className="avatar-edit-button" onClick={() => { setMediaTarget('profile'); setEditingMedia(value => !value) }} aria-label="Edit profile photo">✎</button>{editingMedia && mediaTarget === 'profile' && <div className="media-edit-menu avatar-menu"><button type="button" onClick={() => choose('profile', false)}>🖼️ Gallery</button><button type="button" onClick={() => choose('profile', true)}>📷 Camera</button></div>}</div><div className="profile-public-identity"><h1>{profile.profileName || 'Complete your profile'}</h1><span>{profile.wdId}</span><small>{profile.fullName || 'Work_Disk Social profile'}</small></div><button type="button" className="edit-profile-button" onClick={() => setEditProfile(true)}>✎ Edit profile</button></div>
    <div className="profile-status-row"><div><span className="eyebrow">PROFILE</span><strong>{completion}% complete</strong></div><div className="completion-track"><span style={{ width: `${completion}%` }} /></div></div>
    {previewUrl && <div className="media-editor-backdrop" role="dialog" aria-modal="true"><div className={`media-editor ${mediaTarget === 'cover' ? 'cover-editor' : ''}`}><span className="eyebrow">ADJUST {mediaTarget === 'profile' ? 'PROFILE PHOTO' : 'COVER PHOTO'}</span><h2>Set your photo</h2><p className="gesture-help">Pinch to zoom • Drag to position • Mouse wheel works on desktop</p><div className="media-preview crop-preview" onPointerDown={onPointerDown} onPointerMove={onPointerMove} onPointerUp={onPointerUp} onPointerCancel={onPointerUp} onWheel={onWheel} style={{ touchAction: 'none' }}><img src={previewUrl} alt="Selected preview" style={{ transform: `translate(${crop.x * 12}%, ${crop.y * 12}%) scale(${crop.zoom})` }} /><span className="crop-frame" /></div><button type="button" className="crop-reset" onClick={() => setCrop(DEFAULT_CROP)}>↺ Reset</button><div className="media-editor-actions"><button type="button" onClick={closeMediaEditor}>Cancel</button><button type="button" onClick={() => choose(mediaTarget, false)} disabled={mediaSaving}>Choose another</button><button type="button" className="profile-save" onClick={() => void applyPreview()} disabled={mediaSaving}>{mediaSaving ? 'Saving…' : 'Use photo'}</button></div></div></div>}
    {editProfile && <div className="profile-modal-backdrop"><form className="profile-modal" onSubmit={save}><div className="profile-modal-head"><div><span className="eyebrow">WORK_DISK PROFILE</span><h2>Edit profile</h2></div><button type="button" className="modal-close" onClick={() => setEditProfile(false)}>×</button></div><div className="profile-grid"><label>Profile name<input value={profile.profileName} onChange={event => change('profileName', event.target.value)} placeholder="Public profile name" /></label><label>Full name<input value={profile.fullName} onChange={event => change('fullName', event.target.value)} placeholder="Full name" /></label><label>Age<input type="number" min="1" max="120" value={profile.age ?? ''} onChange={event => change('age', event.target.value)} placeholder="Age" /></label><label>Gender<select value={profile.gender} onChange={event => change('gender', event.target.value as Gender)}><option value="">Select gender</option><option value="female">Female</option><option value="male">Male</option><option value="non-binary">Non-binary</option><option value="prefer-not-to-say">Prefer not to say</option></select></label><label>Mobile / contact<input value={profile.mobile} onChange={event => change('mobile', event.target.value)} placeholder="Contact number" /></label><label>Company <span>(optional)</span><input value={profile.companyName} onChange={event => change('companyName', event.target.value)} placeholder="Company name" /></label></div><div className="profile-system-card"><div><span className="eyebrow">WORK_DISK ID</span><strong>{profile.wdId}</strong><small>Unique system identity for Social search and sending.</small></div><button type="button" className="profile-copy" onClick={() => void navigator.clipboard?.writeText(profile.wdId)}>Copy</button></div><label className="profile-email">Account email <span>(authentication only)</span><input value={identity.email} readOnly /></label>{error && <div className="error">{error}</div>}<div className="modal-actions"><button type="button" onClick={() => setEditProfile(false)}>Cancel</button><button className="profile-save" disabled={saving}>{saving ? 'Saving…' : 'Save profile'}</button></div></form></div>}
    {saved && <div className="profile-saved">Profile updated successfully.</div>}
    <div className="profile-content-placeholder"><span>Posts</span><span>History</span><span>Photos</span><span>Reposts</span></div>
  </section>
}
