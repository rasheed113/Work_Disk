import { doc, getDoc, serverTimestamp, setDoc } from 'firebase/firestore'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { Gender, SocialProfile } from '../../social/domain/profile'
import { firestore } from './config'

const alphabet = 'ABCDEFGHJKLMNPQRSTUVWXYZ23456789'

function generateWdId(): string {
  const bytes = new Uint8Array(9)
  crypto.getRandomValues(bytes)
  return `WD-${Array.from(bytes, byte => alphabet[byte % alphabet.length]).join('')}`
}

function profileFromData(identity: AuthenticatedIdentity, data: Record<string, unknown>): SocialProfile {
  const age = Number(data.age ?? 0)
  return {
    userId: identity.userId,
    email: identity.email,
    wdId: String(data.wdId ?? generateWdId()),
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
    const wdId = profile.wdId || generateWdId()
    const next = { ...profile, userId: identity.userId, email: identity.email, wdId }
    await setDoc(this.reference(identity), {
      ...next,
      updatedAt: serverTimestamp(),
    }, { merge: true })
    return next
  }
}
