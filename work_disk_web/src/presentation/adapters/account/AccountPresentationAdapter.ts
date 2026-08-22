export interface AccountDomainReadModel {
  readonly id: string
  readonly email: string
}

export interface AccountPresentationModel {
  readonly id: string
  readonly email: string
}

/**
 * Presentation boundary for Account BOT-01.
 *
 * This adapter only maps an authoritative Account read model into the
 * presentation shape. It does not call repositories, create identity,
 * authenticate users, or invent Account state.
 */
export class AccountPresentationAdapter {
  toPresentation(account: AccountDomainReadModel): AccountPresentationModel {
    return {
      id: account.id,
      email: account.email,
    }
  }
}
