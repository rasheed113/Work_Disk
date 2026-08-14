# Work_Disk Web — Account — BOT-02
# Profile Assembly Point

## What Is BOT-02?

BOT-02 is the Work_Disk Profile Assembly Point.

It is responsible for assembling and exposing the persistent profile state belonging to an authenticated account.

## BOT-02 Owns

- Profile state
- Display name
- Gender
- Mobile/contact number
- Bio
- Work/business description
- Profile completion state
- Profile completion percentage
- Missing-profile requirements
- Current Profile Picture reference
- Current Cover Picture reference
- Profile history references
- Profile-related privacy references

## BOT-02 Consumes

- BOT-01 authentication/account identity
- Generated Account/Profile IDs
- Media Tool results
- Social/Post content references
- Privacy decisions
- Shared Intelligence advice

## BOT-02 Does Not Own

- Account authentication
- ID generation
- Camera
- Gallery
- Generic editing
- Permanent deletion
- Search
- Notifications
- Feed algorithms
- Intelligence execution

## Key Lifecycle Rule

**Replacement is not deletion.**

When a Profile Picture or Cover Picture is replaced, the previous media remains available through profile history.

Historical media may support:

- View
- Reuse
- Download

Explicit deletion is a separate permanent deletion operation.

## Profile History

The profile may expose authorised historical shared content such as:

- Photos
- Videos
- Text posts
- Profile pictures
- Cover pictures

History preserves applicable date/time and privacy information.

## Privacy

BOT-02 recognises:

- Only Me
- Friends & Followers
- Global

Privacy authorization takes precedence over presentation and intelligence.

## Completion

Profile completion ranges from:

- `0%–99%` — incomplete
- `100%` — complete

Incomplete profiles may expose intelligent completion suggestions.

Shared Intelligence is advisory and cannot silently modify Profile Authority.

## Architecture Principle

**BOT-02 is the Profile Authority and Assembly Point — not a dumping ground for future tools.**

Future tools and Bots remain independently bounded and will connect through explicit contracts.

## Implementation Rule

If a required behaviour is not defined by the current architecture or BOT-02 implementation contract:

**STOP.**

Do not guess. Do not import legacy Work_Disk architecture. Return the decision to architecture first.
