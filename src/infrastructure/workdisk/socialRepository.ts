import type { ActivityEvent, Comment, Post, PostPrivacy, PostReaction } from '../../social/domain/models'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialRepositoryPort } from '../../social/application/ports'
import { emptyReactionCounts, normalizeReactionCounts } from '../../social/domain/reactionCatalog'
import { validatePostContent } from '../../social/domain/validation'
import { firebaseAuth } from '../firebase/config'

const apiBase = (import.meta.env.VITE_WORK_DISK_API_URL as string | undefined)?.replace(/\/$/, '')

type ApiError = { error?: { code?: string; message?: string } }

async function request<T>(method: string, path: string, body?: Record<string, unknown>): Promise<T> {
  const user = firebaseAuth.currentUser
  if (!user) throw new Error('A signed-in Work_Disk account is required.')
  if (!apiBase) throw new Error('Work_Disk Social API URL is not configured for this deployment.')

  const token = await user.getIdToken()
  const response = await fetch(`${apiBase}${path}`, {
    method,
    headers: { Authorization: `Bearer ${token}`, 'Content-Type': 'application/json' },
    body: body ? JSON.stringify(body) : undefined,
  })
  const data = await response.json().catch(() => null) as (T & ApiError) | null
  if (!response.ok) throw new Error(data?.error?.message || `Work_Disk Social API failed (${response.status}).`)
  return data as T
}

function postFromApi(value: Record<string, unknown>): Post {
  const reactionCounts = normalizeReactionCounts(value.reactionCounts)
  return {
    id: String(value.id ?? ''),
    authorId: String(value.authorId ?? ''),
    author: {
      wdId: String(value.wdId ?? value.authorWdId ?? ''),
      profileName: String(value.profileName ?? value.authorProfileName ?? ''),
      photoUrl: String(value.photoUrl ?? value.authorPhotoUrl ?? ''),
    },
    content: String(value.content ?? ''),
    createdAtMs: value.createdAtMs == null ? null : Number(value.createdAtMs),
    likeCount: Number(value.likeCount ?? reactionCounts.like ?? 0),
    privacy: (value.privacy ?? 'public') as PostPrivacy,
    reactionCounts,
    userReaction: value.userReaction ? String(value.userReaction) as PostReaction : null,
    commentCount: Number(value.commentCount ?? 0),
    repostCount: Number(value.repostCount ?? 0),
  }
}

function emptyComment(_postId: string): Comment[] {
  return []
}

export class WorkDiskSocialRepository implements SocialRepositoryPort {
  async createPost(_actor: AuthenticatedIdentity, content: string, privacy: PostPrivacy = 'public', taggedUserIds: string[] = [], mentions: string[] = []): Promise<Post> {
    const clean = validatePostContent(content)
    const created = await request<Record<string, unknown>>('POST', '/api/v1/social/posts', {
      content: clean,
      privacy,
      selectedUserIds: privacy === 'selected_friends' ? taggedUserIds : [],
      taggedUserIds,
      mentions,
    })
    return postFromApi(created)
  }

  subscribeHomeFeed(actor: AuthenticatedIdentity, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void {
    let stopped = false
    let timer: number | null = null
    let delay = 5000

    const schedule = () => {
      if (stopped) return
      timer = window.setTimeout(() => void load(), delay)
    }

    const load = async () => {
      try {
        const data = await request<Record<string, unknown>[]>('GET', '/api/v1/social/feed')
        if (stopped) return
        onChange(data.map(postFromApi))
        delay = 5000
        schedule()
      } catch (cause) {
        if (stopped) return
        onError(cause instanceof Error ? cause : new Error('Failed to load Work_Disk social feed.'))
        // Do not hammer a missing production API every few seconds.
        delay = Math.min(delay * 2, 60000)
        schedule()
      }
    }

    void load()
    return () => {
      stopped = true
      if (timer !== null) window.clearTimeout(timer)
    }
  }

  async updatePost(_actor: AuthenticatedIdentity, postId: string, content: string): Promise<void> {
    await request('PATCH', `/api/v1/social/posts/${encodeURIComponent(postId)}`, { content: validatePostContent(content) })
  }

  async deletePost(_actor: AuthenticatedIdentity, postId: string): Promise<void> {
    await request('DELETE', `/api/v1/social/posts/${encodeURIComponent(postId)}`)
  }

  async updatePostPrivacy(_actor: AuthenticatedIdentity, postId: string, privacy: PostPrivacy, selectedUserIds: string[] = []): Promise<void> {
    await request('PATCH', `/api/v1/social/posts/${encodeURIComponent(postId)}`, {
      privacy,
      selectedUserIds: privacy === 'selected_friends' ? selectedUserIds : [],
    })
  }

  async setPostReaction(_actor: AuthenticatedIdentity, postId: string, reaction: PostReaction | null): Promise<void> {
    await request('POST', `/api/v1/social/posts/${encodeURIComponent(postId)}/reactions`, { reaction })
  }

  subscribeComments(_actor: AuthenticatedIdentity, _postId: string, onChange: (comments: Comment[]) => void, _onError: (error: Error) => void): () => void {
    onChange(emptyComment(_postId))
    return () => undefined
  }

  async createComment(_actor: AuthenticatedIdentity, postId: string, content: string, parentCommentId: string | null = null, mentions: string[] = []): Promise<Comment> {
    const created = await request<Record<string, unknown>>('POST', `/api/v1/social/posts/${encodeURIComponent(postId)}/comments`, {
      content: content.trim(),
      parentCommentId,
      mentions,
    })
    return {
      id: String(created.id ?? ''),
      postId,
      authorId: '',
      author: { wdId: '', profileName: '', photoUrl: '' },
      content: content.trim(),
      parentCommentId,
      createdAtMs: Date.now(),
      editedAtMs: null,
      likeCount: 0,
      reactionCounts: emptyReactionCounts(),
      userReaction: null,
      mentions,
    }
  }

  async updateComment(_actor: AuthenticatedIdentity, postId: string, commentId: string, content: string, mentions: string[] = []): Promise<void> {
    await request('PATCH', `/api/v1/social/posts/${encodeURIComponent(postId)}/comments/${encodeURIComponent(commentId)}`, { content: content.trim(), mentions })
  }

  async deleteComment(_actor: AuthenticatedIdentity, postId: string, commentId: string): Promise<void> {
    await request('DELETE', `/api/v1/social/posts/${encodeURIComponent(postId)}/comments/${encodeURIComponent(commentId)}`)
  }

  async setCommentReaction(_actor: AuthenticatedIdentity, postId: string, commentId: string, reaction: PostReaction | null): Promise<void> {
    await request('POST', `/api/v1/social/posts/${encodeURIComponent(postId)}/comments/${encodeURIComponent(commentId)}/reactions`, { reaction })
  }

  async share(_actor: AuthenticatedIdentity, postId: string): Promise<void> {
    await request('POST', `/api/v1/social/posts/${encodeURIComponent(postId)}/share`, { destination: 'feed' })
  }

  subscribeActivity(_actor: AuthenticatedIdentity, onChange: (events: ActivityEvent[]) => void, _onError: (error: Error) => void): () => void {
    onChange([])
    return () => undefined
  }
}
