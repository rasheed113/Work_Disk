export type PublicAuthor = { wdId: string; profileName: string; photoUrl: string }
export type PostPrivacy = 'public' | 'friends_followers' | 'selected_friends' | 'only_me'
export type Post = { id: string; authorId: string; author: PublicAuthor; content: string; createdAtMs: number | null; likeCount: number; privacy: PostPrivacy }
export type Comment = { id: string; postId: string; authorId: string; author: PublicAuthor; content: string; parentCommentId: string | null; createdAtMs: number | null; editedAtMs: number | null; likeCount: number }
export type PostReaction = 'like' | 'love' | 'haha' | 'wow' | 'sad' | 'angry'
export type ActivityEvent = { id: string; type: 'like' | 'reaction' | 'comment' | 'repost'; actorId: string; targetPostId: string; createdAtMs: number | null }
