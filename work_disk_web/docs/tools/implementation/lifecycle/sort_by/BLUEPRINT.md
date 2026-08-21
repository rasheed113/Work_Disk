# BOT-11 — Sort By Blueprint

BOT-11 is a reusable, multi-caller, domain-neutral ordering boundary.

Flow:

Caller → authority/scope + sort criteria → BOT-11 → provider → ordered opaque target references.

Supported generic fields in this first contract:
- Number
- Size
- Name

Each criterion has an explicit ascending or descending direction. Multiple criteria are accepted so callers can define deterministic tie-breaking without embedding page policy in the bot.

BOT-11 does not search, filter, mark, edit, delete, archive, move, download, or grant authority. It does not mutate source data.
