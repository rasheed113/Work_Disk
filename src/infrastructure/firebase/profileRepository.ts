import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialProfile } from '../../social/domain/profile'
import { firebaseAuth } from './config'

const apiBase = (import.meta.env.VITE_WORK_DISK_API_URL as string | undefined)?.replace(/\/$/, '') || 'http://localhost:8787'

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

export class FirebaseProfileRepository {
  async getProfile(identity: AuthenticatedIdentity): Promise<SocialProfile> {
    const current = await apiRequest('GET')
    return { ...current, userId: identity.userId, email: identity.email }
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
