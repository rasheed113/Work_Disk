import type {
  AccountDomainReadModel,
} from '../adapters/account/AccountPresentationAdapter'

export interface AccountAuthoritativeReadService {
  getAccount(accountId: string): Promise<AccountDomainReadModel | null>
}

export interface AccountEndpointRequest {
  readonly requestId: string
  readonly operation: 'account.get'
  readonly payload: {
    readonly accountId: string
  }
}

export interface AccountEndpointResponse {
  readonly requestId: string
  readonly state: 'AUTHORITATIVE' | 'EMPTY' | 'ERROR'
  readonly payload: AccountDomainReadModel | null
  readonly error: { readonly code: string; readonly message: string } | null
}

/**
 * Reusable transport endpoint boundary for Account authoritative reads.
 *
 * This is deliberately an adapter: it owns request validation and response
 * envelope construction, while AccountAuthoritativeReadService remains the
 * domain authority. A concrete HTTP server can mount this handler without
 * changing the Account BOT contract.
 */
export class AccountWebRuntimeEndpoint {
  constructor(private readonly accountService: AccountAuthoritativeReadService) {}

  async handle(request: AccountEndpointRequest): Promise<AccountEndpointResponse> {
    if (request.operation !== 'account.get') {
      return {
        requestId: request.requestId,
        state: 'ERROR',
        payload: null,
        error: {
          code: 'ACCOUNT_OPERATION_UNRECOGNISED',
          message: 'The requested Account operation is not registered.',
        },
      }
    }

    if (!request.payload.accountId.trim()) {
      return {
        requestId: request.requestId,
        state: 'ERROR',
        payload: null,
        error: {
          code: 'ACCOUNT_ID_REQUIRED',
          message: 'Account ID is required.',
        },
      }
    }

    try {
      const account = await this.accountService.getAccount(request.payload.accountId)

      if (account === null) {
        return {
          requestId: request.requestId,
          state: 'EMPTY',
          payload: null,
          error: null,
        }
      }

      return {
        requestId: request.requestId,
        state: 'AUTHORITATIVE',
        payload: account,
        error: null,
      }
    } catch {
      return {
        requestId: request.requestId,
        state: 'ERROR',
        payload: null,
        error: {
          code: 'ACCOUNT_READ_FAILED',
          message: 'The authoritative Account read failed.',
        },
      }
    }
  }
}
