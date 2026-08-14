# Work_Disk Web — Account — BOT-02
# Profile Assembly Point — Architecture Blueprint

## 1. Primary Responsibility

BOT-02 is the Profile Assembly Point.

Its responsibility is to assemble, manage, and expose the complete persistent profile state belonging to an authenticated account while strictly separating profile authority from identity creation, mutation tools, media acquisition, deletion, search, notifications, feed processing, and shared intelligence execution.

BOT-02 does not become the owner of external tools merely because the profile depends on them.

## 2. Explicit Ownership

BOT-02 owns the authoritative profile assembly domains:

### Core Profile Attributes

- Profile existence state
- Display name
- Gender
- Mobile/contact number
- Bio
- Work/business description

### Profile State

- Profile completion state
- Profile completion percentage
- Missing-profile requirements
- Profile completion suggestions

### Current Media References

- Current Profile Picture reference
- Current Cover Picture reference

### Profile History

- Historical profile media references
- Historical shared-content references exposed through the profile
- History timestamps
- History-related privacy references

### Privacy Reference

BOT-02 maintains profile-related privacy state/references required to assemble the profile.

The authoritative privacy decision itself belongs to the Privacy system.

### ID Handling

BOT-02 consumes Account/Profile ID references.

BOT-02 never generates IDs.

## 3. Dependencies

BOT-02 may consume:

### BOT-01

- Authenticated account identity
- Validated principal information
- Authentication/session context required by the current architecture

### ID Generator

- Account ID
- Profile ID
- Other authorised identity references when required

### Media Tool

- Camera results
- Gallery selections
- Processed media references

### Social/Post System

- Shared posts
- Shared images
- Shared videos
- Shared text content
- Associated media references

### Privacy System

- Viewer visibility rules
- Relationship context
- Privacy decision results

### Shared Intelligence

- Profile completion analytics
- Missing-step suggestions
- Advisory profile improvement information

Shared Intelligence must remain advisory and cannot silently modify BOT-02 authoritative state.

## 4. Hard Boundaries

BOT-02 never owns:

- Account creation
- Authentication processing
- ID generation
- Camera implementation
- Gallery implementation
- Hardware media capture
- Generic editing engines
- Permanent deletion engines
- Search engines
- Search indexing
- Notification dispatch
- Feed ranking
- Feed algorithms
- Core intelligence execution

## 5. Intelligent Profile Completion

Profile completion is not merely a simple field-count calculation.

BOT-02 exposes:

- Completion percentage
- Completion state
- Missing requirements
- Completion suggestions

### Completion States

- `0%–99%` = incomplete
- `100%` = complete

The completion system may use shared intelligence for analysis and recommendations.

Shared Intelligence cannot silently change authoritative profile data.

## 6. Profile Completion Presentation

An incomplete profile may present a completion notice when the profile is visited.

The notice may identify:

- Missing information
- Missing media
- Recommended completion steps
- Priority of completion items

The exact visual presentation belongs to the presentation layer.

## 7. Media Lifecycle

### Replacement Is Not Deletion

Replacing a current Profile Picture or Cover Picture does not delete the previous media.

The previous media becomes historical profile media.

Historical media may support:

- View
- Reuse
- Download

### Explicit Deletion

An explicit delete operation means permanent deletion through the authorised deletion mechanism.

BOT-02 does not implement the permanent deletion engine.

## 8. Profile History

The profile may expose historical shared material, including:

- Profile pictures
- Cover pictures
- Shared images
- Shared videos
- Shared text posts
- Other authorised shared content

Historical entries retain their applicable:

- Creation date/time
- Content/media reference
- Privacy reference

Profile history is not the same as the dashboard feed.

## 9. Privacy

Supported profile visibility tiers:

### Only Me

Visible only to the profile owner.

### Friends & Followers

Visible only within the authorised relationship context.

### Global

Visible within Work_Disk's authorised global visibility boundary.

Global does not automatically mean unrestricted external/public-internet exposure.

## 10. Privacy Precedence

Privacy authorization must occur before protected profile information is exposed.

Intelligence must never bypass privacy.

A viewer must never receive protected profile content merely because an intelligence or presentation layer requested it.

## 11. Request Lifecycle

Request
  ↓
BOT-01 Principal Validation
  ↓
Validated Principal
  ↓
Privacy / Viewer Context
  ↓
Profile Assembly
  ↓
Current Profile State
  +
Current Media
  +
Authorised History
  +
Completion State
  ↓
Unified Profile Payload
  ↓
Consuming / Presentation Layer

## 12. Architectural Decision Gate

If implementation encounters a requirement not defined by the current architecture or approved BOT-02 implementation contract:

STOP.

Do not guess.

Do not import previous Work_Disk architecture.

Do not derive a new architectural rule from implementation convenience.

Return the missing decision to architecture.

## 13. BOT-02 Principle

BOT-02 is the Profile Authority and Assembly Point.

It coordinates profile information without becoming a dumping ground for unrelated tools.

Every external responsibility must remain with its proper future Bot, Tool, or shared system.
