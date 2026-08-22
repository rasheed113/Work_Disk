export interface StatusStripItem {
  id: string
  sourceId: string
  text: string
  occurredAt: string
  priority: number
  expiresAt?: string
}

export interface StatusStripSource {
  id: string
  readStatusItems(): readonly StatusStripItem[]
}

export class StatusStripBot {
  constructor(private readonly sources: readonly StatusStripSource[]) {}

  read(now = new Date()): StatusStripItem[] {
    const nowMs = now.getTime()
    const items = this.sources.flatMap((source) => source.readStatusItems())

    return items
      .filter((item) => !item.expiresAt || Date.parse(item.expiresAt) > nowMs)
      .sort((left, right) => right.priority - left.priority || Date.parse(right.occurredAt) - Date.parse(left.occurredAt) || left.id.localeCompare(right.id))
  }
}
