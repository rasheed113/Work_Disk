import { firebaseAuth } from '../firebase/config'
import { FirebaseProfileRepository } from '../firebase/profileRepository'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialProfile } from '../../social/domain/profile'

const apiBase = (import.meta.env.VITE_WORK_DISK_API_URL as string | undefined)?.replace(/\/$/, '') || 'http://localhost:8787'
const legacyRepository = new FirebaseProfileRepository()

class WorkDiskApiUnavailableError extends Error {
  constructor(cause: unknown) {
    super(cause instanceof Error ? cause.message : 'Work_Disk API is unavailable.')
    this.name = 'WorkDiskApiUnavailableError'
  }
}

async function token(): Promise<string> {
  const user = firebaseAuth.currentUser
  if (!user) throw new Error('A signed-in Work_Disk account is required.')
  return user.getIdToken()
}

async function request(path: string, method: 'GET' | 'PATCH', body?: Record<string, unknown>): Promise<SocialProfile> {
  const idToken = await token()
  let response: Response
  try {
    response = await fetch(`${apiBase}${path}`, {
      method,
      headers: { Authorization: `Bearer ${idToken}`, 'Content-Type': 'application/json' },
      body: body ? JSON.stringify(body) : undefined,
    })
  } catch (cause) {
    throw new WorkDiskApiUnavailableError(cause)
  }

  const envelope = await response.json().catch(() => null) as { payload?: SocialProfile; error?: { message?: string } } | null
  if (!response.ok || !envelope?.payload) throw new Error(envelope?.error?.message || `Work_Disk API request failed (${response.status}).`)
  return envelope.payload
}

export class WorkDiskProfileRepository {
  async getProfile(identity: AuthenticatedIdentity): Promise<SocialProfile> {
    try {
      return await request('/api/v1/profile', 'GET')
    } catch (cause) {
      if (!(cause instanceof WorkDiskApiUnavailableError)) throw cause

      // The API is the authoritative production store. When the API is temporarily
      // unreachable, keep the profile page usable by reading the existing Firebase
      // migration store. We deliberately do not write to the legacy store here.
      return await legacyRepository.getProfile(identity)
    }
  }

  async saveProfile(identity: AuthenticatedIdentity, profile: SocialProfile): Promise<SocialProfile> {
    const saved = await request('/api/v1/profile', 'PATCH', {
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
