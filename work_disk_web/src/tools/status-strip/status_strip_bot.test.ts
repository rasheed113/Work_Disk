import { describe, expect, it } from 'vitest'
import { StatusStripBot, type StatusStripSource } from './status_strip_bot'

describe('StatusStripBot', () => {
  it('aggregates authorised sources, removes expired items and applies stable priority ordering', () => {
    const source: StatusStripSource = {
      id: 'activity-bot',
      readStatusItems: () => [
        { id: 'older-high', sourceId: 'activity-bot', text: 'High', occurredAt: '2026-08-22T09:00:00Z', priority: 10 },
        { id: 'newer-low', sourceId: 'activity-bot', text: 'Low', occurredAt: '2026-08-22T10:00:00Z', priority: 1 },
        { id: 'expired', sourceId: 'activity-bot', text: 'Expired', occurredAt: '2026-08-22T08:00:00Z', priority: 99, expiresAt: '2026-08-22T09:30:00Z' },
      ],
    }

    const bot = new StatusStripBot([source])
    const result = bot.read(new Date('2026-08-22T11:00:00Z'))

    expect(result.map((item) => item.id)).toEqual(['older-high', 'newer-low'])
  })
})
