import type { AccountProfileModel } from './model'

export function AccountProfileSurface({ model }: { model: AccountProfileModel | null }) {
  return (
    <section className="wd-feature-surface wd-account-profile-surface" aria-labelledby="account-profile-title">
      <div className="wd-feature-surface__heading">
        <p className="wd-feature-surface__eyebrow">ACCOUNT / PROFILE</p>
        <h1 id="account-profile-title">Your Work_Disk identity</h1>
        <p className="wd-feature-surface__description">
          Authoritative account and profile information is presented here through the feature contract.
        </p>
      </div>

      {model ? (
        <article className="wd-feature-card wd-feature-card--3d">
          <div>
            <span className="wd-feature-card__label">Display name</span>
            <strong>{model.displayName}</strong>
          </div>
          <div>
            <span className="wd-feature-card__label">Account ID</span>
            <strong>{model.accountId}</strong>
          </div>
          {model.profileCompletion !== undefined && (
            <div>
              <span className="wd-feature-card__label">Profile completion</span>
              <strong>{model.profileCompletion}%</strong>
            </div>
          )}
        </article>
      ) : (
        <article className="wd-feature-card wd-feature-card--empty" role="status">
          <span className="wd-feature-card__label">No active profile context</span>
          <p>Authoritative account/profile data has not been supplied to this presentation surface.</p>
        </article>
      )}
    </section>
  )
}
