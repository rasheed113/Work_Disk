# Action Board

Action Board is a reusable capability-discovery and routing boundary for marked/selected targets.

It answers: **Which actions are applicable here?**

It does not answer: **May I execute this action?** That remains the responsibility of the selected action tool at execution time.

## Relationship

- BOT-09 owns selection.
- Action Board discovers applicable actions.
- Individual action tools execute operations.
- UI renders the returned descriptors.
