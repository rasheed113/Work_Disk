# Social v1 Implementation Report

## Implemented

- React/Vite web shell.
- Firebase Authentication boundary.
- Firestore infrastructure adapter.
- Provider-neutral Social application ports.
- Authenticated identity value.
- Real Post creation with user-supplied content.
- Authoritative Firestore persistence.
- Realtime Home feed read-back.
- Atomic idempotent Like transaction.
- Activity event generated from the Like transaction.
- Mobile-first Social navigation shell.
- Explicit non-functional states for future Inbox, Video, Comments, Reposts, and Shares.
- Firebase Hosting configuration.
- Firestore security rules.
- CI workflow for typecheck, tests, and production build.
- Manual Firebase deployment workflow.

## Tests included

- Post validation tests.
- Social provider-boundary tests.

## Security model

Protected Firestore operations require Firebase Authentication. Post ownership is enforced by `authorId`. Like identity is enforced by the authenticated UID. Post like-count mutation and activity creation are tied to the atomic like write through `getAfter` security checks.

## Not falsely marked complete

A real deployed runtime cannot be verified until a Firebase project is connected and its configuration/secrets are supplied. The application intentionally fails explicitly when Firebase web configuration is absent instead of showing fake data.

Required deployment inputs are documented in `docs/social/FIREBASE_SETUP.md`.

## Acceptance target

`real identity → real post → Firestore persistence → fresh Home read → real like → real activity`
