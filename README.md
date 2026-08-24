# Work_Disk

Work_Disk is a modern social web platform with posts, video, messaging, profiles, notifications, and a future productivity workspace.

## Current product

The first product boundary is the **Social Web**. Dashboard is intentionally outside the Social product architecture and is exposed only as a top-right navigation destination.

### Social navigation

Top:
- Inbox 📥
- Activity shortcuts
- → Dashboard

Bottom:
- Home 🏠
- Post ➕
- Video 🎬
- Profile 🧑‍💼

## Real vertical slice

`Authenticated Identity → Home Read → Create Post → Firestore Persistence → Home Read-back → Atomic Like → Activity Event`

The implementation contains no seed posts, fake counters, hardcoded user identity, or mock success path. Empty data is shown as an explicit empty state.

## Architecture

`Presentation → Application Contracts → Domain → Infrastructure Ports → Firebase`

Firebase SDKs terminate at the infrastructure boundary. Domain/application code remains provider-neutral.

## Engineering workflow

`Architecture → Attack → Boundary → Blueprint → Contract → Implementation → Tests → Security/Runtime Verification → Deployment Verification`

## Firebase

The first provider adapter is Firebase Authentication + Firestore + Firebase Hosting. Configuration is supplied through environment variables; privileged deployment credentials remain GitHub secrets.

See `docs/social/FIREBASE_SETUP.md` for the real-data setup and acceptance procedure.
