import { describe, expect, it } from 'vitest'
import { componentRegistry, getEligibleComponents } from './componentRegistry'

describe('component registry',()=>{
 it('contains the locked 40 component registrations',()=>{expect(componentRegistry).toHaveLength(40)})
 it('exposes only eligible registrations',()=>{expect(getEligibleComponents().every(c=>c.eligible)).toBe(true)})
})
