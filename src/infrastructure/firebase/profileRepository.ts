import { doc, getDoc, serverTimestamp, setDoc } from 'firebase/firestore'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { Gender, SocialProfile } from '../../social/domain/profile'
import { firestore } from './config'

const alphabet = 'ABCDEFGHJKLMNPQRSTUVWXYZ23456789'

/**
 * Creates a stable, user-specific WD ID from the Firebase Auth UID.
 *
 * Unlike random client-side generation, the same authenticated UID always
 * produces the same WD ID, so a user cannot accidentally receive a second
 * WD ID after a reload or profile re-creation. Firebase Auth UIDs are unique,
 * therefore the encoding is unique for every authenticated user.
 */
function generateWdId(userId: string): string {
  let hash = 2166136261
  for (let index = 0; index < userId.length; index += 1) {
    hash ^= userId.charCodeAt(index)
    hash = Math.imul(hash, 16777619)
  }

  let value = hash >>> 0
  let code = ''
  for (let index = 0; index < 8; index += 1) {
    code += alphabet[value % alphabet.length]
    value = Math.floor(value / alphabet.length)
  }

  return `WD-${code}`
}

function profileFromData(identity: AuthenticatedIdentity, data: Record<string, unknown>): SocialProfile {
  const age = Number(data.age ?? 0)
  return {
    userId: identity.userId,
    email: identity.email,
    wdId: String(data.wdId ?? generateWdId(identity.userId)),
    profileName: String(data.profileName ?? ''),
    fullName: String(data.fullName ?? ''),
    age: age > 0 ? age : null,
    gender: String(data.gender ?? '') as Gender,
    mobile: String(data.mobile ?? ''),
    companyName: String(data.companyName ?? ''),
    photoUrl: String(data.photoUrl ?? ''),
    coverUrl: String(data.coverUrl ?? ''),
    updatedAtMs: null,
  }
}

export class FirebaseProfileRepository {
  private reference(identity: AuthenticatedIdentity) {
    return doc(firestore, 'profiles', identity.userId)
  }

  async getProfile(identity: AuthenticatedIdentity): Promise<SocialProfile> {
    const snapshot = await getDoc(this.reference(identity))
    if (!snapshot.exists()) {
      const profile = profileFromData(identity, {})
      await setDoc(this.reference(identity), {
        ...profile,
        createdAt: serverTimestamp(),
        updatedAt: serverTimestamp(),
      }, { merge: true })
      return profile
    }
    return profileFromData(identity, snapshot.data())
  }

  async saveProfile(identity: AuthenticatedIdentity, profile: SocialProfile): Promise<SocialProfile> {
    const existing = await getDoc(this.reference(identity))
    const existingWdId = existing.exists() ? String(existing.data().wdId ?? '') : ''
    const wdId = existingWdId || profile.wdId || generateWdId(identity.userId)
    const next = { ...profile, userId: identity.userId, email: identity.email, wdId }

    await setDoc(this.reference(identity), {
      ...next,
      updatedAt: serverTimestamp(),
    }, { merge: true })

    return next
  }
}
