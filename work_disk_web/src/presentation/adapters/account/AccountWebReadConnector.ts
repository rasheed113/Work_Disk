import type {
  WebTransportProvider,
  WebTransportResponse,
} from '../../transport/realtime-web-transport'
import {
  AccountPresentationAdapter,
  type AccountDomainReadModel,
  type AccountPresentationModel,
} from './AccountPresentationAdapter'

export const ACCOUNT_READ_OPERATION = 'account.get' as const

export interface AccountReadRequest {
  readonly accountId: string
}

/**
 * Authoritative Web read connector for Account BOT-01.
 *
 * Transport remains responsible for delivery; BOT-01 remains responsible for
 * Account authority; this connector only binds the two and maps the returned
 * domain read model into presentation state.
 */
export class AccountWebReadConnector {
  constructor(
    private readonly transport: WebTransportProvider<
      AccountReadRequest,
      AccountDomainReadModel
    >,
    private readonly adapter = new AccountPresentationAdapter(),
    private readonly correlationIdFactory: () => string = () => crypto.randomUUID(),
  ) {}

  async read(accountId: string): Promise<AccountPresentationModel | null> {
    const response: WebTransportResponse<AccountDomainReadModel> =
      await this.transport.request({
        operation: ACCOUNT_READ_OPERATION,
        payload: { accountId },
        correlationId: this.correlationIdFactory(),
      })

    if (response.state === 'EMPTY') return null
    if (!response.payload) {
      throw new Error('ACCOUNT_AUTHORITATIVE_PAYLOAD_MISSING')
    }

    return this.adapter.toPresentation(response.payload)
  }
}
