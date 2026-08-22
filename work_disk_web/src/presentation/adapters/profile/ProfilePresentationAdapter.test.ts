import { describe, expect, it } from 'vitest'
import { profilePresentationAdapter } from './ProfilePresentationAdapter'

describe('ProfilePresentationAdapter', () => {
  it('projects only authoritative profile identity fields', () => {
    expect(
      profilePresentationAdapter.toDashboardProfile({
        profile: {
          accountId: 'account-1',
          profileId: 'profile-1',
          displayName: 'Rasheed',
        },
      }),
    ).toEqual({ accountId: 'account-1', displayName: 'Rasheed' })
  })

  it('returns null when authoritative profile data is unavailable', () => {
    expect(
      profilePresentationAdapter.toDashboardProfile({ profile: null }),
    ).toBeNull()
  })

  it('does not fabricate missing identity data', () => {
    expect(
      profilePresentationAdapter.toDashboardProfile({
        profile: { accountId: '', profileId: 'profile-1', displayName: '' },
      }),
    ).toBeNull()
  })
})
