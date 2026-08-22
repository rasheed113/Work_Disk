# Status Strip Bot — Implementation Contract

## Boundary

Status Strip Bot is a read-only aggregation boundary for dashboard status presentation. It accepts status items from authorised source adapters and returns display-safe status items. It does not own domain truth, mutate source data, or implement source-specific business rules.

## Source contract

Each source exposes `readStatusItems()` and owns its own authoritative read path. A source may represent a BOT, service, or domain adapter. Status Strip Bot must not invent source data when a source returns no items.

## Aggregation rules

1. Collect items from all registered sources.
2. Drop expired items.
3. Sort by descending priority, then newest occurrence time, then stable item ID.
4. Return a new read-only result list to the presentation adapter.
5. Dashboard presentation owns animation, colour, typography, and layout.

## Presentation boundary

The Dashboard Status Strip is a non-card presentation surface. It is rendered outside the dashboard card grid and may animate right-to-left. The strip must never become an authority or persistence boundary.
