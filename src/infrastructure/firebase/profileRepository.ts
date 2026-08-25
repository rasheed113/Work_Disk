import { doc, getDoc, serverTimestamp, setDoc } from 'firebase/firestore'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { Gender, SocialProfile } from '../../social/domain/profile'
import { firestore } from './config'

function generateWdId(userId: string): string {
  const encoded = btoa(userId).replace(/\+/g, '-').replace(/\//g, '_').replace(/=+$/g, '')
  return `WD-${encoded}`
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
      await this.persistPublicProfile(profile)
      await setDoc(this.reference(identity), {
        ...profile,
        createdAt: serverTimestamp(),
        updatedAt: serverTimestamp(),
      }, { merge: true })
      return profile
    }
    const profile = profileFromData(identity, snapshot.data())
    await this.persistPublicProfile(profile)
    return profile
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
    await this.persistPublicProfile(next)
    return next
  }

  private async persistPublicProfile(profile: SocialProfile): Promise<void> {
    if (!profile.wdId || !profile.profileName.trim()) return
    await setDoc(doc(firestore, 'publicProfiles', profile.userId), {
      wdId: profile.wdId,
      profileName: profile.profileName.trim(),
      photoUrl: profile.photoUrl,
      updatedAt: serverTimestamp(),
    }, { merge: true })
  }
}
