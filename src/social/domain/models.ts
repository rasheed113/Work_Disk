export type PublicAuthor = {
  wdId: string
  profileName: string
  photoUrl: string
}

export type Post = {
  id: string
  authorId: string
  author: PublicAuthor
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
