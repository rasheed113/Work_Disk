# Firebase Setup — Social v1

The Social implementation is provider-isolated, but the first infrastructure adapter is Firebase.

## Firebase project

Create a Firebase project and enable:

1. Authentication → Email/Password
2. Firestore Database
3. Firebase Hosting

Deploy `firestore.rules` before exposing the application to users.

## Local web configuration

Copy `.env.example` to `.env` and fill every `VITE_FIREBASE_*` value from the Firebase Web App configuration.

Never commit `.env`.

## GitHub deployment secrets

The manual deployment workflow expects:

- `VITE_FIREBASE_API_KEY`
- `VITE_FIREBASE_AUTH_DOMAIN`
- `VITE_FIREBASE_PROJECT_ID`
- `VITE_FIREBASE_STORAGE_BUCKET`
- `VITE_FIREBASE_MESSAGING_SENDER_ID`
- `VITE_FIREBASE_APP_ID`
- `FIREBASE_SERVICE_ACCOUNT`

The Firebase web configuration is not treated as a privileged secret; it identifies the web app. The service-account credential is privileged and must remain a GitHub secret.

## Real-data acceptance

After deployment:

1. Register a real account.
2. Sign in.
3. Open Post.
4. Enter real content.
5. Publish.
6. Confirm Home receives the persisted post from Firestore.
7. Like the post.
8. Confirm the like count changes from the authoritative transaction.
9. Confirm Activity reports the real like event.
10. Refresh the browser and confirm the post remains because it is persisted, not local UI state.

If Firebase configuration is missing, the application intentionally fails with an explicit configuration error instead of rendering fake data.
