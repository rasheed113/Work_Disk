export type Post = {
  id: string
  authorId: string
  authorEmail: string
  content: string
  createdAtMs: number | null
  likeCount: number
}

export type ActivityEvent = {
  id: string
  type: 'like'
  actorId: string
  targetPostId: string
  createdAtMs: number | null
}
