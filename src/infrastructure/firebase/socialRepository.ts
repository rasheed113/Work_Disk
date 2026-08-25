import { addDoc, collection, doc, getDoc, onSnapshot, orderBy, query, runTransaction, serverTimestamp, where } from 'firebase/firestore'
import type { ActivityEvent, Comment, Post, PostPrivacy, PostReaction } from '../../social/domain/models'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialRepositoryPort } from '../../social/application/ports'
import { validatePostContent } from '../../social/domain/validation'
import { firestore } from './config'
import { FirebaseProfileRepository } from './profileRepository'
import { emptyReactionCounts, normalizeReactionCounts } from '../../social/domain/reactionCatalog'

const profiles = new FirebaseProfileRepository()
type Snapshot = { id: string; data: () => Record<string, unknown> }

function counts(value: unknown): Record<PostReaction, number> {
  return normalizeReactionCounts(value)
}

function postFromSnapshot(snapshot: Snapshot): Post {
  const data = snapshot.data()
  const timestamp = data.createdAt as { toMillis?: () => number } | undefined
  return {
    id: snapshot.id,
    authorId: String(data.authorId ?? ''),
    author: {
      wdId: String(data.authorWdId ?? ''),
      profileName: String(data.authorProfileName ?? ''),
      photoUrl: String(data.authorPhotoUrl ?? ''),
    },
    content: String(data.content ?? ''),
    createdAtMs: timestamp?.toMillis?.() ?? null,
    likeCount: Number(data.likeCount ?? 0),
    privacy: (data.privacy ?? 'public') as PostPrivacy,
    reactionCounts: counts(data.reactionCounts),
    userReaction: null,
    commentCount: Number(data.commentCount ?? 0),
    repostCount: Number(data.repostCount ?? 0),
  }
}

function commentFromSnapshot(snapshot: Snapshot): Comment {
  const data = snapshot.data()
  const created = data.createdAt as { toMillis?: () => number } | undefined
  const edited = data.editedAt as { toMillis?: () => number } | undefined
  return {
    id: snapshot.id,
    postId: String(data.postId ?? ''),
    authorId: String(data.authorId ?? ''),
    author: {
      wdId: String(data.authorWdId ?? ''),
      profileName: String(data.authorProfileName ?? ''),
      photoUrl: String(data.authorPhotoUrl ?? ''),
    },
    content: String(data.content ?? ''),
    parentCommentId: data.parentCommentId ? String(data.parentCommentId) : null,
    createdAtMs: created?.toMillis?.() ?? null,
    editedAtMs: edited?.toMillis?.() ?? null,
    likeCount: Number(data.likeCount ?? 0),
    reactionCounts: counts(data.reactionCounts),
    userReaction: null,
    mentions: Array.isArray(data.mentions) ? data.mentions.map(String) : [],
  }
}

async function reactionFor(path: ReturnType<typeof doc>): Promise<PostReaction | null> {
  const snapshot = await getDoc(path)
  if (!snapshot.exists()) return null
  return String(snapshot.data().type) as PostReaction
}

export class FirebaseSocialRepository implements SocialRepositoryPort {
  async createPost(actor: AuthenticatedIdentity, content: string, privacy: PostPrivacy = 'public', taggedUserIds: string[] = [], mentions: string[] = []): Promise<Post> {
    const clean = validatePostContent(content)
    const profile = await profiles.getProfile(actor)
    const profileName = profile.profileName.trim()
    const profilePhoto = profile.photoUrl.trim()
    if (!profileName || !profilePhoto) throw new Error('PROFILE_REQUIRED: complete your profile name and picture before creating a post')
    const reference = await addDoc(collection(firestore, 'posts'), {
      authorId: actor.userId,
      authorWdId: profile.wdId,
      authorProfileName: profileName,
      authorPhotoUrl: profilePhoto,
      content: clean,
      privacy,
      selectedUserIds: privacy === 'selected_friends' ? taggedUserIds : [],
      taggedUserIds,
      mentions,
      likeCount: 0,
      commentCount: 0,
      repostCount: 0,
      reactionCounts: emptyReactionCounts(),
      createdAt: serverTimestamp(),
    })
    const snapshot = await getDoc(reference)
    if (!snapshot.exists()) throw new Error('PROVIDER_FAILURE: created post disappeared')
    return postFromSnapshot(snapshot)
  }

  subscribeHomeFeed(actor: AuthenticatedIdentity, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void {
    const feed = query(collection(firestore, 'posts'), orderBy('createdAt', 'desc'))
    return onSnapshot(feed, snapshot => {
      void Promise.all(snapshot.docs.map(async item => {
        const post = postFromSnapshot(item)
        const userReaction = await reactionFor(doc(firestore, 'posts', item.id, 'reactions', actor.userId))
        return { ...post, userReaction }
      })).then(onChange).catch(onError)
    }, onError)
  }

  async updatePost(actor: AuthenticatedIdentity, postId: string, content: string): Promise<void> {
    const clean = validatePostContent(content)
    const ref = doc(firestore, 'posts', postId)
    await runTransaction(firestore, async transaction => {
      const post = await transaction.get(ref)
      if (!post.exists() || post.data().authorId !== actor.userId) throw new Error('FORBIDDEN: only the post owner can edit it')
      transaction.update(ref, { content: clean, editedAt: serverTimestamp() })
    })
  }

  async deletePost(actor: AuthenticatedIdentity, postId: string): Promise<void> {
    const ref = doc(firestore, 'posts', postId)
    await runTransaction(firestore, async transaction => {
      const post = await transaction.get(ref)
      if (!post.exists() || post.data().authorId !== actor.userId) throw new Error('FORBIDDEN: only the post owner can delete it')
      transaction.delete(ref)
    })
  }

  async updatePostPrivacy(actor: AuthenticatedIdentity, postId: string, privacy: PostPrivacy, selectedUserIds: string[] = []): Promise<void> {
    const ref = doc(firestore, 'posts', postId)
    await runTransaction(firestore, async transaction => {
      const post = await transaction.get(ref)
      if (!post.exists() || post.data().authorId !== actor.userId) throw new Error('FORBIDDEN: only the post owner can change privacy')
      transaction.update(ref, { privacy, selectedUserIds: privacy === 'selected_friends' ? selectedUserIds : [] })
    })
  }

  async setPostReaction(actor: AuthenticatedIdentity, postId: string, reaction: PostReaction | null): Promise<void> {
    const postRef = doc(firestore, 'posts', postId)
    const reactionRef = doc(firestore, 'posts', postId, 'reactions', actor.userId)
    await runTransaction(firestore, async transaction => {
      const post = await transaction.get(postRef)
      const existing = await transaction.get(reactionRef)
      if (!post.exists()) throw new Error('NOT_FOUND: post does not exist')
      const previous = existing.exists() ? String(existing.data().type) as PostReaction : null
      if (previous === reaction) return
      const current = counts(post.data().reactionCounts)
      if (previous) current[previous] = Math.max(0, current[previous] - 1)
      if (reaction) current[reaction] = Number(current[reaction] ?? 0) + 1
      transaction.update(postRef, { reactionCounts: current, likeCount: current.like })
      if (reaction) transaction.set(reactionRef, { actorId: actor.userId, postId, type: reaction, createdAt: serverTimestamp() })
      else if (existing.exists()) transaction.delete(reactionRef)
    })
  }

  subscribeComments(actor: AuthenticatedIdentity, postId: string, onChange: (comments: Comment[]) => void, onError: (error: Error) => void): () => void {
    const commentsQuery = query(collection(firestore, 'posts', postId, 'comments'), orderBy('createdAt', 'asc'))
    return onSnapshot(commentsQuery, snapshot => {
      void Promise.all(snapshot.docs.map(async item => {
        const comment = commentFromSnapshot(item)
        const userReaction = await reactionFor(doc(firestore, 'posts', postId, 'comments', item.id, 'reactions', actor.userId))
        return { ...comment, userReaction }
      })).then(onChange).catch(onError)
    }, onError)
  }

  async createComment(actor: AuthenticatedIdentity, postId: string, content: string, parentCommentId: string | null = null, mentions: string[] = []): Promise<Comment> {
    const clean = content.trim()
    if (!clean) throw new Error('VALIDATION_FAILED: comment cannot be empty')
    const profile = await profiles.getProfile(actor)
    const postRef = doc(firestore, 'posts', postId)
    const commentRef = doc(collection(firestore, 'posts', postId, 'comments'))
    await runTransaction(firestore, async transaction => {
      const post = await transaction.get(postRef)
      if (!post.exists()) throw new Error('NOT_FOUND: post does not exist')
      transaction.set(commentRef, {
        postId,
        authorId: actor.userId,
        authorWdId: profile.wdId,
        authorProfileName: profile.profileName,
        authorPhotoUrl: profile.photoUrl,
        content: clean,
        parentCommentId,
        mentions,
        likeCount: 0,
        reactionCounts: emptyReactionCounts(),
        createdAt: serverTimestamp(),
        editedAt: null,
      })
      transaction.update(postRef, { commentCount: Number(post.data().commentCount ?? 0) + 1 })
    })
    const snapshot = await getDoc(commentRef)
    if (!snapshot.exists()) throw new Error('PROVIDER_FAILURE: comment was not created')
    return commentFromSnapshot(snapshot)
  }

  async updateComment(actor: AuthenticatedIdentity, postId: string, commentId: string, content: string, mentions: string[] = []): Promise<void> {
    const clean = content.trim()
    if (!clean) throw new Error('VALIDATION_FAILED: comment cannot be empty')
    const ref = doc(firestore, 'posts', postId, 'comments', commentId)
    await runTransaction(firestore, async transaction => {
      const comment = await transaction.get(ref)
      if (!comment.exists() || comment.data().authorId !== actor.userId) throw new Error('FORBIDDEN: only the comment owner can edit it')
      transaction.update(ref, { content: clean, mentions, editedAt: serverTimestamp() })
    })
  }

  async deleteComment(actor: AuthenticatedIdentity, postId: string, commentId: string): Promise<void> {
    const postRef = doc(firestore, 'posts', postId)
    const commentRef = doc(firestore, 'posts', postId, 'comments', commentId)
    await runTransaction(firestore, async transaction => {
      const post = await transaction.get(postRef)
      const comment = await transaction.get(commentRef)
      if (!post.exists() || !comment.exists()) throw new Error('NOT_FOUND: comment does not exist')
      if (comment.data().authorId !== actor.userId && post.data().authorId !== actor.userId) throw new Error('FORBIDDEN: only the comment owner or post owner can delete it')
      transaction.delete(commentRef)
      transaction.update(postRef, { commentCount: Math.max(0, Number(post.data().commentCount ?? 0) - 1) })
    })
  }

  async setCommentReaction(actor: AuthenticatedIdentity, postId: string, commentId: string, reaction: PostReaction | null): Promise<void> {
    const commentRef = doc(firestore, 'posts', postId, 'comments', commentId)
    const reactionRef = doc(firestore, 'posts', postId, 'comments', commentId, 'reactions', actor.userId)
    await runTransaction(firestore, async transaction => {
      const comment = await transaction.get(commentRef)
      const existing = await transaction.get(reactionRef)
      if (!comment.exists()) throw new Error('NOT_FOUND: comment does not exist')
      const previous = existing.exists() ? String(existing.data().type) as PostReaction : null
      if (previous === reaction) return
      const current = counts(comment.data().reactionCounts)
      if (previous) current[previous] = Math.max(0, current[previous] - 1)
      if (reaction) current[reaction] = Number(current[reaction] ?? 0) + 1
      transaction.update(commentRef, { reactionCounts: current, likeCount: current.like })
      if (reaction) transaction.set(reactionRef, { actorId: actor.userId, type: reaction, createdAt: serverTimestamp() })
      else if (existing.exists()) transaction.delete(reactionRef)
    })
  }

  async share(actor: AuthenticatedIdentity, postId: string): Promise<void> {
    const post = await getDoc(doc(firestore, 'posts', postId))
    if (!post.exists()) throw new Error('NOT_FOUND: post does not exist')
    await addDoc(collection(firestore, 'postShares'), { actorId: actor.userId, postId, createdAt: serverTimestamp() })
  }

  subscribeActivity(actor: AuthenticatedIdentity, onChange: (events: ActivityEvent[]) => void, onError: (error: Error) => void): () => void {
    const activityQuery = query(collection(firestore, 'activities'), where('actorId', '==', actor.userId))
    return onSnapshot(activityQuery, snapshot => onChange(snapshot.docs.map(item => {
      const data = item.data()
      const timestamp = data.createdAt as { toMillis?: () => number } | undefined
      return {
        id: item.id,
        type: String(data.type) as ActivityEvent['type'],
        actorId: String(data.actorId ?? ''),
        targetPostId: String(data.targetPostId ?? ''),
        createdAtMs: timestamp?.toMillis?.() ?? null,
      }
    })), onError)
  }
}
