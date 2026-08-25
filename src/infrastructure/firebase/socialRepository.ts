import { addDoc, collection, doc, onSnapshot, orderBy, query, runTransaction, serverTimestamp, where, getDoc } from 'firebase/firestore'
import type { ActivityEvent, Post, PublicAuthor } from '../../social/domain/models'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialRepositoryPort } from '../../social/application/ports'
import { validatePostContent } from '../../social/domain/validation'
import { firestore } from './config'
import { FirebaseProfileRepository } from './profileRepository'

const profiles = new FirebaseProfileRepository()

type Snapshot = { id: string; data: () => Record<string, unknown> }

function authorFromPublicProfile(data: Record<string, unknown>): PublicAuthor {
  return {
    wdId: String(data.wdId ?? ''),
    profileName: String(data.profileName ?? ''),
    photoUrl: String(data.photoUrl ?? ''),
  }
}

async function resolveAuthor(authorId: string, data: Record<string, unknown>): Promise<PublicAuthor> {
  const stored: PublicAuthor = {
    wdId: String(data.authorWdId ?? ''),
    profileName: String(data.authorProfileName ?? ''),
    photoUrl: String(data.authorPhotoUrl ?? ''),
  }

  if (stored.wdId && stored.profileName) return stored

  const publicProfile = await getDoc(doc(firestore, 'publicProfiles', authorId))
  if (publicProfile.exists()) return authorFromPublicProfile(publicProfile.data())

  return stored
}

async function postFromSnapshot(snapshot: Snapshot): Promise<Post> {
  const data = snapshot.data()
  const timestamp = data.createdAt as { toMillis?: () => number } | undefined
  return {
    id: snapshot.id,
    authorId: String(data.authorId ?? ''),
    author: await resolveAuthor(String(data.authorId ?? ''), data),
    content: String(data.content ?? ''),
    createdAtMs: timestamp?.toMillis?.() ?? null,
    likeCount: Number(data.likeCount ?? 0),
  }
}

export class FirebaseSocialRepository implements SocialRepositoryPort {
  async createPost(actor: AuthenticatedIdentity, content: string): Promise<Post> {
    const clean = validatePostContent(content)
    const profile = await profiles.getProfile(actor)
    if (!profile.wdId || !profile.profileName.trim()) {
      throw new Error('PROFILE_REQUIRED: complete your Work_Disk profile name and WD ID before posting')
    }

    const reference = await addDoc(collection(firestore, 'posts'), {
      authorId: actor.userId,
      authorWdId: profile.wdId,
      authorProfileName: profile.profileName.trim(),
      authorPhotoUrl: profile.photoUrl,
      content: clean,
      audience: 'authenticated',
      likeCount: 0,
      createdAt: serverTimestamp(),
    })

    return new Promise<Post>((resolve, reject) => {
      const unsubscribe = onSnapshot(doc(firestore, 'posts', reference.id), async snapshot => {
        if (!snapshot.exists()) {
          unsubscribe()
          reject(new Error('PROVIDER_FAILURE: created post disappeared'))
          return
        }
        try {
          const post = await postFromSnapshot(snapshot)
          if (post.createdAtMs === null) return
          unsubscribe()
          resolve(post)
        } catch (error) {
          unsubscribe()
          reject(error)
        }
      }, error => {
        unsubscribe()
        reject(error)
      })
    })
  }

  subscribeHomeFeed(_actor: AuthenticatedIdentity, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void {
    const feed = query(collection(firestore, 'posts'), orderBy('createdAt', 'desc'))
    return onSnapshot(feed, snapshot => {
      Promise.all(snapshot.docs.map(postFromSnapshot))
        .then(onChange)
        .catch(error => onError(error instanceof Error ? error : new Error('Failed to resolve post authors')))
    }, error => onError(error))
  }

  async likePost(actor: AuthenticatedIdentity, postId: string): Promise<void> {
    if (!postId) throw new Error('VALIDATION_FAILED: postId is required')
    const postRef = doc(firestore, 'posts', postId)
    const likeRef = doc(firestore, 'posts', postId, 'likes', actor.userId)
    const activityRef = doc(firestore, 'activities', `${actor.userId}_${postId}_like`)
    await runTransaction(firestore, async transaction => {
      const post = await transaction.get(postRef)
      if (!post.exists()) throw new Error('NOT_FOUND: post does not exist')
      const like = await transaction.get(likeRef)
      if (like.exists()) return
      transaction.set(likeRef, { actorId: actor.userId, postId, createdAt: serverTimestamp() })
      transaction.update(postRef, { likeCount: Number(post.data().likeCount ?? 0) + 1 })
      transaction.set(activityRef, { type: 'like', actorId: actor.userId, targetPostId: postId, createdAt: serverTimestamp() })
    })
  }

  subscribeActivity(actor: AuthenticatedIdentity, onChange: (events: ActivityEvent[]) => void, onError: (error: Error) => void): () => void {
    const activityQuery = query(collection(firestore, 'activities'), where('actorId', '==', actor.userId))
    return onSnapshot(activityQuery, snapshot => {
      const events = snapshot.docs.map(item => {
        const data = item.data()
        const timestamp = data.createdAt as { toMillis?: () => number } | undefined
        return { id: item.id, type: 'like' as const, actorId: String(data.actorId ?? ''), targetPostId: String(data.targetPostId ?? ''), createdAtMs: timestamp?.toMillis?.() ?? null }
      }).sort((a, b) => (b.createdAtMs ?? 0) - (a.createdAtMs ?? 0))
      onChange(events)
    }, error => onError(error))
  }
}
