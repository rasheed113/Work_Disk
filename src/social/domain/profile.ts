export type Gender = 'female' | 'male' | 'non-binary' | 'prefer-not-to-say' | ''

export type SocialProfile = {
  userId: string
  email: string
  wdId: string
  profileName: string
  fullName: string
  age: number | null
  gender: Gender
  mobile: string
  companyName: string
  photoUrl: string
  coverUrl: string
  updatedAtMs: number | null
}

export const REQUIRED_PROFILE_FIELDS = [
  'profileName',
  'fullName',
  'age',
  'gender',
  'mobile',
  'photoUrl',
  'coverUrl',
] as const

export function profileCompletion(profile: SocialProfile): number {
  const complete = REQUIRED_PROFILE_FIELDS.filter(field => {
    const value = profile[field]
    return field === 'age' ? typeof value === 'number' && value > 0 : typeof value === 'string' ? value.trim().length > 0 : Boolean(value)
  }).length
  return Math.round((complete / REQUIRED_PROFILE_FIELDS.length) * 100)
}
