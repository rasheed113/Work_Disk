import type { DashboardProfile } from '../../dashboard/model/dashboard'

/**
 * Transport-neutral projection of the authoritative BOT-02 ProfileAssembly.
 *
 * This is deliberately a DTO boundary: the presentation layer does not import
 * ProfileRepository or mutate BOT-02 state. A future Web transport adapter
 * (API/WASM/etc.) is responsible for producing this snapshot from the
 * authoritative ProfileService::assemble(...) result.
 */
export interface AuthoritativeProfileAssemblySnapshot {
  profile: {
    accountId: string
    profileId: string
    displayName: string
  } | null
}

export interface ProfilePresentationAdapter {
  toDashboardProfile(
    assembly: AuthoritativeProfileAssemblySnapshot,
  ): DashboardProfile | null
}

export const profilePresentationAdapter: ProfilePresentationAdapter = {
  toDashboardProfile(assembly) {
    if (!assembly.profile) return null

    const { accountId, displayName } = assembly.profile

    if (!accountId || !displayName) return null

    return { accountId, displayName }
  },
}
