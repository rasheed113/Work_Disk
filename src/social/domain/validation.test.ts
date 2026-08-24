import { describe, expect, it } from 'vitest'
import { validatePostContent } from './validation'

describe('post validation', () => {
  it('accepts real user content', () => {
    expect(validatePostContent('  Hello Work_Disk  ')).toBe('Hello Work_Disk')
  })

  it('rejects empty content', () => {
    expect(() => validatePostContent('   ')).toThrow('VALIDATION_FAILED')
  })

  it('rejects content beyond the contract limit', () => {
    expect(() => validatePostContent('x'.repeat(5001))).toThrow('VALIDATION_FAILED')
  })
})
