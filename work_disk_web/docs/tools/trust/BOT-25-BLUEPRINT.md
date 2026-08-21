# BOT-25 Blueprint

Flow: authorised moderation actor → validate request → ModerationProvider → moderation result.

BOT-25 does not independently decide policy, delete content, suspend accounts, or grant authority. Provider owns policy and enforcement semantics.