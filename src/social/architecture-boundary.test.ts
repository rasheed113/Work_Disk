import { describe, expect, it } from 'vitest'
import { readFileSync } from 'node:fs'
import { resolve } from 'node:path'

function read(path: string): string {
  return readFileSync(resolve(process.cwd(), path), 'utf8')
}

describe('Social architecture boundary', () => {
  it('keeps Firebase imports out of the domain', () => {
    expect(read('src/social/domain/models.ts')).not.toContain('firebase/')
    expect(read('src/social/domain/identity.ts')).not.toContain('firebase/')
    expect(read('src/social/domain/validation.ts')).not.toContain('firebase/')
  })

  it('keeps Firebase imports out of the application ports', () => {
    expect(read('src/social/application/ports.ts')).not.toContain("from 'firebase/")
  })
})
