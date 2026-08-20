# Work_Disk Bot Naming Registry

## Canonical Naming Rule

Every implementation Bot is identified by **both** its stable Bot number and its canonical functional name.

> **Bot Identifier = BOT number + canonical functional name.**

The number provides stable identity. The functional name provides semantic identity.

The canonical functional name MUST be used wherever a human-readable Bot identity is required, including architecture documentation, blueprints, implementation contracts, roadmaps, READMEs, profiles, completion records, tests, and repository-facing documentation.

Directory and source paths may retain the stable machine identifier (`bot-XX`) for filesystem stability.

## Confirmed Repository Names

| Bot | Canonical functional name | Repository boundary |
|---|---|---|
| **BOT-01** | **Account Authentication Foundation** | `src/account/bot-01/` |
| **BOT-02** | **Profile Authority & Assembly Point** | `src/account/bot-02/` |
| **BOT-03** | **Public Identifier Tool** | `src/tools/...` / Tool-Bot-03 identifier boundary |
| **BOT-04** | **Not present in the inspected repository baseline** | Do not invent a name |
| **BOT-05** | **Evidence Verification Bot** | `src/evidence/bot-05/` |

## Naming Safety Rule

A missing Bot implementation or missing authoritative name must never be filled by guesswork.

If BOT-04 or any future Bot has no authoritative functional name, implementation stops at the naming decision until the architecture/specification supplies that name.

## BOT-05 Canonical Identity

**BOT-05 — Evidence Verification Bot**

Its implementation boundary is:

`src/evidence/bot-05/`

Its documentation boundary is:

`docs/evidence/implementation/bot-05/`

## Next Bot

The next implementation slot is:

**BOT-06 — Canonical functional name must be established from the approved architecture before implementation begins.**
