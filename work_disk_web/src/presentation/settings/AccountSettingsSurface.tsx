import { getPageProperty } from '../page-properties/page-property-registry'
import type { AccountPresentationModel } from '../adapters/account/AccountPresentationAdapter'

export function AccountSettingsSurface({ account }: { account: AccountPresentationModel | null }) {
  const accountProperty = getPageProperty('account')

  if (accountProperty?.availability !== 'AVAILABLE') return null

  return (
    <section aria-label="Account settings" className="wd-account-settings-surface">
      <h2>Account</h2>
      {account ? (
        <div>
          <p>{account.email}</p>
          <p>{account.id}</p>
        </div>
      ) : (
        <p>Account data is supplied by the authoritative Account BOT-01 path.</p>
      )}
    </section>
  )
}
