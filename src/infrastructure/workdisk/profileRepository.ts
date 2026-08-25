import { firebaseAuth } from '../firebase/config'
import { LegacyFirebaseProfileRepository } from '../firebase/legacyProfileRepository'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialProfile } from '../../social/domain/profile'

const apiBase = (import.meta.env.VITE_WORK_DISK_API_URL as string | undefined)?.replace(/\/$/, '')
const legacyRepository = new LegacyFirebaseProfileRepository()

async function token(): Promise<string> {
  const user = firebaseAuth.currentUser
  if (!user) throw new Error('A signed-in Work_Disk account is required.')
  return user.getIdToken()
}

async function request(method: 'GET' | 'PATCH', body?: Record<string, unknown>): Promise<SocialProfile> {
  if (!apiBase) throw new Error('Work_Disk Account API URL is not configured.')

  const idToken = await token()
  const response = await fetch(`${apiBase}/api/v1/profile`, {
    method,
    headers: { Authorization: `Bearer ${idToken}`, 'Content-Type': 'application/json' },
    body: body ? JSON.stringify(body) : undefined,
  })
  const envelope = await response.json().catch(() => null) as { payload?: SocialProfile; error?: { message?: string } } | null
  if (!response.ok || !envelope?.payload) {
    throw new Error(envelope?.error?.message || `Work_Disk Profile API failed (${response.status}).`)
  }
  return envelope.payload
}

export class WorkDiskProfileRepository {
  async getProfile(identity: AuthenticatedIdentity): Promise<SocialProfile> {
    try {
      return await request('GET')
    } catch (error) {
      // API is authoritative when available. If the API is not reachable/configured,
      // keep the Profile page readable from the existing Firebase migration store.
      // Never attempt an API write from the read fallback.
      const legacy = await legacyRepository.getProfile(identity)
      if (legacy.profileName || legacy.fullName || legacy.mobile || legacy.companyName || legacy.photoUrl || legacy.coverUrl) {
        return legacy
      }
      throw error
    }
  }

  async saveProfile(identity: AuthenticatedIdentity, profile: SocialProfile): Promise<SocialProfile> {
    const saved = await request('PATCH', {
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
