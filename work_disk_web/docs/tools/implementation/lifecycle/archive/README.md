# BOT-06 — Archive 📦

Generic lifecycle Tool Bot for authorised archive/unarchive operations across multiple domains.

### Boundary
Caller/domain decides policy and authority. BOT-06 executes only the archive lifecycle through injected boundaries.

### Explicitly separate from
- BOT-04 Delete 🗑️
- BOT-05 Trash 🗑️
- Mark/selection
- Search/filter
- Notification delivery
- Domain permissions

### Core rule
> Archive preserves a resource as non-active state; it does not destroy it or manufacture authority.

See `BLUEPRINT.md`, `IMPLEMENTATION_CONTRACT.md`, `ATTACKS.md`, and `ROADMAP.md` for the sealed implementation boundary.
