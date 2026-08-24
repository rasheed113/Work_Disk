# Social Tests, Security, Runtime and Deployment Gates

## Tests

The first implementation must provide tests for:

1. Post validation.
2. Post persistence and read-back.
3. Like idempotency.
4. Activity event creation.
5. Authorisation for private/owned resources.
6. Page navigation contract.
7. Provider adapter isolation.

## Security / runtime verification

Verify:

- authenticated identity is required for protected writes;
- users cannot mutate another user's post;
- users cannot create duplicate likes through retries;
- private data is not returned to unauthorised callers;
- Firebase credentials/configuration intended for privileged environments never enter the browser bundle;
- realtime events cannot bypass domain authorisation;
- browser UI does not claim success before the authoritative write succeeds.

## Deployment verification

Deployment is not considered successful merely because a build completes.

Required evidence:

`source commit → CI green → deployed revision → reachable web application → authenticated session → real post write → real post read → real like/activity result`

A deployment with only static UI or mock data fails this gate.

## Final report

The final report must separate:

- implemented;
- tested;
- security verified;
- runtime verified;
- deployment verified;
- remaining gaps.

No unverified claim may be reported as complete.
