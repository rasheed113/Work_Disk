# BOT-05 — Trash 🗑️ Roadmap

## Phase 1 — Architecture
- [x] Define Trash ownership boundary.
- [x] Define 3-calendar-month retention policy.
- [x] Separate restore from permanent destruction.
- [x] Define Empty Trash semantics.
- [x] Identify race, replay, expiry and preservation attacks.

## Phase 2 — Contracts
- [x] Define TrashEntry.
- [x] Define storage lifecycle claims.
- [x] Define restore boundary.
- [x] Define destruction boundary.
- [x] Define injected retention policy and trusted time.
- [x] Define explicit results and failures.

## Phase 3 — Implementation
- [x] Implement public request/result models.
- [x] Implement TrashTool lifecycle orchestration.
- [x] Keep persistence and domain restoration/destruction behind interfaces.
- [x] Avoid hardcoded domain IDs, payload formats, or UI behaviour.

## Phase 4 — Verification
- [x] Add unit contract tests.
- [ ] Compile in repository-native CI/toolchain.
- [ ] Run repository CI after PR creation.
- [ ] Review integration with Delete Bot and authoritative persistence.

## Phase 5 — Integration
- [ ] Wire Delete Bot's authoritative deletion path to durable Trash intake before irreversible source destruction.
- [ ] Provide production TrashStore implementation.
- [ ] Provide production restore/destruction boundaries.
- [ ] Register a scheduler to call expiry purge.
- [ ] Add UI integration for Trash 🗑️, Restore ↩️, Delete One 🗑️ and Empty Trash 🗑️.

## Completion

BOT-05 architecture and reference implementation are complete for the bounded tool layer. Production integration remains explicitly tracked rather than being silently invented inside the bot.
