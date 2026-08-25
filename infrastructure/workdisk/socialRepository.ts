import type { ActivityEvent, Comment, Post, PostPrivacy, PostReaction } from '../../social/domain/models'
import type { AuthenticatedIdentity } from '../../social/domain/identity'
import type { SocialRepositoryPort } from '../../social/application/ports'
import { validatePostContent } from '../../social/domain/validation'

const baseUrl = (import.meta.env.VITE_WORK_DISK_SOCIAL_API_URL || 'http://localhost:8787').replace(/\/$/, '')

type ApiPost = { id: string; authorId: string; wdId: string; profileName: string; photoUrl: string; content: string; privacy: PostPrivacy; createdAtMs: number; editedAtMs?: number }

async function request<T>(identity: AuthenticatedIdentity, path: string, init: RequestInit = {}): Promise<T> {
  const headers = new Headers(init.headers)
  headers.set('Content-Type', 'application/json')
  headers.set('X-Work-Disk-User', identity.userId)
  const response = await fetch(`${baseUrl}${path}`, { ...init, headers })
  const body = await response.json().catch(() => null)
  if (!response.ok) throw new Error(body?.error?.message || `Work_Disk Social request failed (${response.status})`)
  return body as T
}

function postFromApi(value: ApiPost): Post {
  return {
    id: value.id,
    authorId: value.authorId,
    author: { wdId: value.wdId, profileName: value.profileName, photoUrl: value.photoUrl },
    content: value.content,
    createdAtMs: value.createdAtMs,
    likeCount: 0,
    privacy: value.privacy,
    reactionCounts: {} as Record<PostReaction, number>,
    userReaction: null,
    commentCount: 0,
    repostCount: 0,
  }
}

export class WorkDiskSocialRepository implements SocialRepositoryPort {
  async createPost(actor: AuthenticatedIdentity, content: string, privacy: PostPrivacy = 'public', taggedUserIds: string[] = [], mentions: string[] = []): Promise<Post> {
    const clean = validatePostContent(content)
    const profileName = window.localStorage.getItem(`wd.profile.${actor.userId}.name`) || ''
    const photoUrl = window.localStorage.getItem(`wd.profile.${actor.userId}.photo`) || ''
    const wdId = window.localStorage.getItem(`wd.profile.${actor.userId}.id`) || actor.userId
    if (!profileName.trim()) throw new Error('PROFILE_REQUIRED: Work_Disk profile name is required before posting')
    const result = await request<{ id: string; createdAtMs: number }>(actor, '/api/v1/social/posts', { method: 'POST', body: JSON.stringify({ actorId: actor.userId, wdId, profileName, photoUrl, content: clean, privacy, taggedUserIds, mentions, selectedUserIds: privacy === 'selected_friends' ? taggedUserIds.join(',') : '' }) })
    return { id: result.id, authorId: actor.userId, author: { wdId, profileName, photoUrl }, content: clean, createdAtMs: result.createdAtMs, likeCount: 0, privacy, reactionCounts: {} as Record<PostReaction, number>, userReaction: null, commentCount: 0, repostCount: 0 }
  }

  subscribeHomeFeed(actor: AuthenticatedIdentity, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void {
    let stopped = false
    const load = async () => { try { const result = await request<ApiPost[]>(actor, '/api/v1/social/feed'); if (!stopped) onChange(result.map(postFromApi)) } catch (error) { if (!stopped) onError(error instanceof Error ? error : new Error('Feed request failed')) } }
    void load(); const timer = window.setInterval(load, 3000); return () => { stopped = true; window.clearInterval(timer) }
  }

  async updatePost(actor: AuthenticatedIdentity, postId: string, content: string): Promise<void> { await request(actor, `/api/v1/social/posts/${postId}`, { method: 'PATCH', body: JSON.stringify({ content: validatePostContent(content) }) }) }
  async deletePost(actor: AuthenticatedIdentity, postId: string): Promise<void> { await request(actor, `/api/v1/social/posts/${postId}`, { method: 'DELETE' }) }
  async updatePostPrivacy(actor: AuthenticatedIdentity, postId: string, privacy: PostPrivacy, selectedUserIds: string[] = []): Promise<void> { await request(actor, `/api/v1/social/posts/${postId}`, { method: 'PATCH', body: JSON.stringify({ privacy, selectedUserIds: selectedUserIds.join(',') }) }) }
  async setPostReaction(actor: AuthenticatedIdentity, postId: string, reaction: PostReaction | null): Promise<void> { await request(actor, `/api/v1/social/posts/${postId}/reactions`, { method: 'POST', body: JSON.stringify({ reaction: reaction || '' }) }) }
  subscribeComments(actor: AuthenticatedIdentity, postId: string, onChange: (comments: Comment[]) => void, onError: (error: Error) => void): () => void { void actor; void postId; onChange([]); onError(new Error('Work_Disk comments endpoint is being migrated next.')); return () => {} }
  async createComment(): Promise<Comment> { throw new Error('Work_Disk comment migration is next; Firebase is no longer used for Social writes.') }
  async updateComment(): Promise<void> { throw new Error('Work_Disk comment migration is next.') }
  async deleteComment(): Promise<void> { throw new Error('Work_Disk comment migration is next.') }
  async setCommentReaction(): Promise<void> { throw new Error('Work_Disk comment migration is next.') }
  async share(actor: AuthenticatedIdentity, postId: string): Promise<void> { await request(actor, `/api/v1/social/posts/${postId}/share`, { method: 'POST', body: JSON.stringify({ destination: 'external' }) }) }
  async likePost(actor: AuthenticatedIdentity, postId: string): Promise<void> { await this.setPostReaction(actor, postId, 'like') }
  subscribeActivity(_actor: AuthenticatedIdentity, onChange: (events: ActivityEvent[]) => void): () => void { onChange([]); return () => {} }
}
