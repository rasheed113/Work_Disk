export function validatePostContent(content: string): string {
  const clean = content.trim()
  if (!clean) throw new Error('VALIDATION_FAILED: post content is required')
  if (clean.length > 5000) throw new Error('VALIDATION_FAILED: post content is too long')
  return clean
}
