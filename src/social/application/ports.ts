import type { User } from 'firebase/auth'
import type { ActivityEvent, Post } from '../domain/models'

export interface IdentityPort {
  currentUser(): User | null
}

export interface SocialRepositoryPort {
  createPost(actor: User, content: string): Promise<Post>
  subscribeHomeFeed(actor: User, onChange: (posts: Post[]) => void, onError: (error: Error) => void): () => void
  likePost(actor: User, postId: string): Promise<void>
  subscribeActivity(actor: User, onChange: (events: ActivityEvent[]) => void, onError: (error: Error) => void): () => void
}
