import type { ActivityEvent, Post } from '../domain/models'
import type { AuthenticatedIdentity } from '../domain/identity'

export interface IdentityPort {
  currentIdentity(): AuthenticatedIdentity | null
}

export interface SocialRepositoryPort {
  createPost(actor: AuthenticatedIdentity, content: string): Promise<Post>
  subscribeHomeFeed(actor: AuthenticatedIdentity, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void
  likePost(actor: AuthenticatedIdentity, postId: string): Promise<void>
  subscribeActivity(actor: AuthenticatedIdentity, onChange: (events: ActivityEvent[]) => void, onError: (error: Error) => void): () => void
}
