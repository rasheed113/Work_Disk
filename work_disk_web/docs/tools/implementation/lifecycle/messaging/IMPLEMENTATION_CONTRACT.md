# BOT-17 Implementation Contract

A valid command requires request, authority, conversation scope, actor, target, content, idempotency and expected-version references. Authority MUST be evaluated before provider invocation. The provider owns persistence, transport and concrete conversation policy. This tool MUST NOT perform UI work, grant authority, or mutate unrelated domain state.
