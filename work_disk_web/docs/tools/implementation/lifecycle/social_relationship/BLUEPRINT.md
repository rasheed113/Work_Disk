# BOT-14 — Social Relationship Blueprint

```text
Caller / Domain
      |
      v
RelationshipCommand
      |
      v
BOT-14 Social Relationship
      |
  authority + validity gate
      |
      v
RelationshipProvider
      |
      v
RelationshipResult
```

BOT-14 owns the reusable relationship-command boundary for follow/unfollow and connection request lifecycle operations. Block/mute, recommendation, feed ranking, notifications and moderation remain separate capabilities.
