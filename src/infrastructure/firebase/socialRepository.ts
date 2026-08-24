import { collection, doc, onSnapshot, orderBy, query, runTransaction, serverTimestamp, where, addDoc } from 'firebase/firestore'
import type { ActivityEvent, Post } from '../../social/domain/models'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialRepositoryPort } from '../../social/application/ports'
import { firestore } from './config'

function postFromSnapshot(snapshot: { id: string; data: () => Record<string, unknown> }): Post {
  const data = snapshot.data()
  const timestamp = data.createdAt as { toMillis?: () => number } | undefined
  return {
    id: snapshot.id,
    authorId: String(data.authorId ?? ''),
    authorEmail: String(data.authorEmail ?? ''),
    content: String(data.content ?? ''),
    createdAtMs: timestamp?.toMillis?.() ?? null,
    likeCount: Number(data.likeCount ?? 0),
  }
}

export class FirebaseSocialRepository implements SocialRepositoryPort {
  async createPost(actor: AuthenticatedIdentity, content: string): Promise<Post> {
    const clean = content.trim()
    if (!clean) throw new Error('VALIDATION_FAILED: post content is required')
    if (clean.length > 5000) throw new Error('VALIDATION_FAILED: post content is too long')

    const reference = await addDoc(collection(firestore, 'posts'), {
      authorId: actor.userId,
      authorEmail: actor.email,
      content: clean,
      audience: 'authenticated',
      likeCount: 0,
      createdAt: serverTimestamp(),
    })

    const created = await new Promise<Post>((resolve, reject) => {
      const unsubscribe = onSnapshot(doc(firestore, 'posts', reference.id), snapshot => {
        if (!snapshot.exists()) {
          unsubscribe()
          reject(new Error('PROVIDER_FAILURE: created post disappeared'))
          return
        }
        const post = postFromSnapshot(snapshot)
        if (post.createdAtMs === null) return
        unsubscribe()
        resolve(post)
      }, error => {
        unsubscribe()
        reject(error)
      })
    })

    return created
  }

  subscribeHomeFeed(actor: AuthenticatedIdentity, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void {
    const feed = query(collection(firestore, 'posts'), orderBy('createdAt', 'desc'))
    return onSnapshot(feed, snapshot => {
      const posts = snapshot.docs
        .map(docSnapshot => postFromSnapshot(docSnapshot))
        .filter(post => post.authorId === actor.userId || post.authorId.length > 0)
      onChange(posts)
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

      const currentCount = Number(post.data().likeCount ?? 0)
      transaction.set(likeRef, {
        actorId: actor.userId,
        postId,
        createdAt: serverTimestamp(),
      })
      transaction.update(postRef, { likeCount: currentCount + 1 })
      transaction.set(activityRef, {
        type: 'like',
        actorId: actor.userId,
        targetPostId: postId,
        createdAt: serverTimestamp(),
      })
    })
  }

  subscribeActivity(actor: AuthenticatedIdentity, onChange: (events: ActivityEvent[]) => void, onError: (error: Error) => void): () => void {
    const activityQuery = query(
      collection(firestore, 'activities'),
      where('actorId', '==', actor.userId),
      orderBy('createdAt', 'desc'),
    )
    return onSnapshot(activityQuery, snapshot => {
      onChange(snapshot.docs.map(item => {
        const data = item.data()
        const timestamp = data.createdAt as { toMillis?: () => number } | undefined
        return {
          id: item.id,
          type: 'like',
          actorId: String(data.actorId ?? ''),
          targetPostId: String(data.targetPostId ?? ''),
          createdAtMs: timestamp?.toMillis?.() ?? null,
        }
      }))
    }, error => onError(error))
  }
}
