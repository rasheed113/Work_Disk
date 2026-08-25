import type { ActivityEvent, Comment, Post, PostPrivacy, PostReaction } from '../domain/models'
import type { AuthenticatedIdentity } from '../domain/identity'

export interface IdentityPort { currentIdentity(): AuthenticatedIdentity | null }

export interface SocialRepositoryPort {
  createPost(actor: AuthenticatedIdentity, content: string, privacy?: PostPrivacy, taggedUserIds?: string[], mentions?: string[]): Promise<Post>
  subscribeHomeFeed(actor: AuthenticatedIdentity, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void
  updatePost(actor: AuthenticatedIdentity, postId: string, content: string): Promise<void>
  deletePost(actor: AuthenticatedIdentity, postId: string): Promise<void>
  updatePostPrivacy(actor: AuthenticatedIdentity, postId: string, privacy: PostPrivacy, selectedUserIds?: string[]): Promise<void>
  setPostReaction(actor: AuthenticatedIdentity, postId: string, reaction: PostReaction | null): Promise<void>
  subscribeComments(actor: AuthenticatedIdentity, postId: string, onChange: (comments: Comment[]) => void, onError: (error: Error) => void): () => void
  createComment(actor: AuthenticatedIdentity, postId: string, content: string, parentCommentId?: string | null, mentions?: string[]): Promise<Comment>
  updateComment(actor: AuthenticatedIdentity, postId: string, commentId: string, content: string, mentions?: string[]): Promise<void>
  deleteComment(actor: AuthenticatedIdentity, postId: string, commentId: string): Promise<void>
  setCommentReaction(actor: AuthenticatedIdentity, postId: string, commentId: string, reaction: PostReaction | null): Promise<void>
  share(actor: AuthenticatedIdentity, postId: string): Promise<void>
  subscribeActivity(actor: AuthenticatedIdentity, onChange: (events: ActivityEvent[]) => void, onError: (error: Error) => void): () => void
}
