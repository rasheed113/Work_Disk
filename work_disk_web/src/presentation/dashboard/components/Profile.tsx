import type { DashboardProfile } from '../model/dashboard'

export function Profile({ profile }: { profile: DashboardProfile | null }) {
  return <div>{profile ? <><strong>{profile.displayName}</strong><p>Account ID: {profile.accountId}</p></> : <p>No profile context is available.</p>}</div>
}
