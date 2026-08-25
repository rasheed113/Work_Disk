import { doc, getDoc, serverTimestamp, setDoc } from 'firebase/firestore'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { Gender, SocialProfile } from '../../social/domain/profile'
import { firestore } from './config'

function generateWdId(userId: string): string {
  const encoded = btoa(userId).replace(/\+/g, '-').replace(/\//g, '_').replace(/=+$/g, '')
  return `WD-${encoded}`
}

export class LegacyFirebaseProfileRepository {
  private reference(identity: AuthenticatedIdentity) { return doc(firestore, 'profiles', identity.userId) }

  async getProfile(identity: AuthenticatedIdentity): Promise<SocialProfile> {
    const snapshot = await getDoc(this.reference(identity))
    if (!snapshot.exists()) {
      const profile: SocialProfile = { userId: identity.userId, email: identity.email, wdId: generateWdId(identity.userId), profileName: '', fullName: '', age: null, gender: '', mobile: '', companyName: '', photoUrl: '', coverUrl: '', updatedAtMs: null }
      await setDoc(this.reference(identity), { ...profile, createdAt: serverTimestamp(), updatedAt: serverTimestamp() }, { merge: true })
      return profile
    }
    const data = snapshot.data()
    const age = Number(data.age ?? 0)
    return { userId: identity.userId, email: identity.email, wdId: String(data.wdId ?? generateWdId(identity.userId)), profileName: String(data.profileName ?? ''), fullName: String(data.fullName ?? ''), age: age > 0 ? age : null, gender: String(data.gender ?? '') as Gender, mobile: String(data.mobile ?? ''), companyName: String(data.companyName ?? ''), photoUrl: String(data.photoUrl ?? ''), coverUrl: String(data.coverUrl ?? ''), updatedAtMs: null }
  }
}
