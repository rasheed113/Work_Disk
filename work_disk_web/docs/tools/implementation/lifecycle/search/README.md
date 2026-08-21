# BOT-08 — Search 🔎 README

**Number:** 08  
**Category:** Search Tool Bot  
**Call model:** Multi-caller / domain-neutral  
**Mutation:** None

BOT-08 provides one reusable generic search boundary for multiple pages and domains. It validates a search request, checks the supplied authority, and delegates retrieval to the supplied search provider.

It supports Exact, Keyword, Prefix, Identifier, and Filter modes without hardcoding page or domain policy.

BOT-08 does not own permissions, account/role isolation policy, lifecycle visibility, field projection, ranking, indexing, notifications, or mutations.
