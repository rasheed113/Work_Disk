/**
 * Dashboard presentation boundary.
 *
 * This adapter intentionally contains no domain/business logic and does not
 * invent fallback data. BOT contracts remain authoritative; callers provide
 * only data already obtained through an authorised BOT read path.
 */

export type DashboardBotAvailability = 'AVAILABLE' | 'EMPTY' | 'UNAVAILABLE'

export interface DashboardBotPresentation<T> {
  readonly availability: DashboardBotAvailability
  readonly data: T | null
}

export function presentBotResult<T>(
  result: T | null | undefined,
): DashboardBotPresentation<T> {
  if (result === undefined) {
    return { availability: 'UNAVAILABLE', data: null }
  }

  if (result === null) {
    return { availability: 'EMPTY', data: null }
  }

  return { availability: 'AVAILABLE', data: result }
}
