# BOT-09 — Mark / Unmark 🔖

**Number:** 09  
**Category:** Selection / Marking Tool Bot  
**Call model:** Multi-caller / domain-neutral  
**Mutation:** Selection-state only

BOT-09 provides one reusable selection boundary for multiple pages and domains. It supports individual mark/unmark, Mark All within an authorised scope, and clearing selection.

Marking is not permission and does not execute any downstream action. A separate action/capability layer can expose applicable tools such as Delete, Move, Archive, Download, or Export. Each selected-item operation must revalidate its own authority and current state.

Long press, checkboxes, selection bars, bottom sheets, and action presentation remain outside BOT-09.
