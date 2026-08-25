import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialProfile } from '../../social/domain/profile'
import { firebaseAuth } from './config'
import { LegacyFirebaseProfileRepository } from './legacyProfileRepository'

const apiBase = (import.meta.env.VITE_WORK_DISK_API_URL as string | undefined)?.replace(/\/$/, '') || 'http://localhost:8787'
const legacy = new LegacyFirebaseProfileRepository()

async function idToken(): Promise<string> {
  const user = firebaseAuth.currentUser
  if (!user) throw new Error('A signed-in Work_Disk account is required.')
  return user.getIdToken()
}

async function apiRequest(method: 'GET' | 'PATCH', body?: Record<string, unknown>): Promise<SocialProfile> {
  const token = await idToken()
  const response = await fetch(`${apiBase}/api/v1/profile`, {
    method,
    headers: { Authorization: `Bearer ${token}`, 'Content-Type': 'application/json' },
    body: body ? JSON.stringify(body) : undefined,
  })
  const data = await response.json().catch(() => null) as { payload?: SocialProfile; error?: { message?: string } } | null
  if (!response.ok || !data?.payload) throw new Error(data?.error?.message || `Work_Disk Profile API failed (${response.status}).`)
  return data.payload
}

function needsMigration(profile: SocialProfile): boolean {
  return !profile.profileName && !profile.fullName && !profile.photoUrl && !profile.coverUrl && !profile.mobile && !profile.companyName && profile.age === null && !profile.gender
}

export class FirebaseProfileRepository {
  async getProfile(identity: AuthenticatedIdentity): Promise<SocialProfile> {
    const current = await apiRequest('GET')
    if (!needsMigration(current)) return current

    const old = await legacy.getProfile(identity)
    const migrated = await this.saveProfile(identity, old)
    return migrated
  }

  async saveProfile(identity: AuthenticatedIdentity, profile: SocialProfile): Promise<SocialProfile> {
    const saved = await apiRequest('PATCH', {
      profileName: profile.profileName,
      fullName: profile.fullName,
      age: profile.age ?? '',
      gender: profile.gender,
      mobile: profile.mobile,
      companyName: profile.companyName,
      photoUrl: profile.photoUrl,
      coverUrl: profile.coverUrl,
    })
    return { ...saved, userId: identity.userId, email: identity.email }
  }
}
