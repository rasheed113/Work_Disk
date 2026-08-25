import type { PostReaction } from './models'

export const REACTION_OPTIONS: readonly PostReaction[] = [
  'like',
  'love',
  'care',
  'haha',
  'wow',
  'sad',
  'angry',
  'support',
  'celebrate',
  'insightful',
  'curious',
  'grateful',
]

export const REACTION_EMOJI: Record<PostReaction, string> = {
  like: '👍',
  love: '❤️',
  care: '🥰',
  haha: '😂',
  wow: '😮',
  sad: '😢',
  angry: '😡',
  support: '🤝',
  celebrate: '🎉',
  insightful: '💡',
  curious: '🤔',
  grateful: '🙏',
}

export function emptyReactionCounts(): Record<PostReaction, number> {
  return Object.fromEntries(REACTION_OPTIONS.map(type => [type, 0])) as Record<PostReaction, number>
}

export function normalizeReactionCounts(value: unknown): Record<PostReaction, number> {
  const source = value && typeof value === 'object' ? value as Record<string, unknown> : {}
  return Object.fromEntries(REACTION_OPTIONS.map(type => [type, Number(source[type] ?? 0)])) as Record<PostReaction, number>
}
