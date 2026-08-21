# Work_Disk Master Tool Inventory v2

## Status

**Purpose:** establish the grand-project tool inventory, identify missing capabilities, and define the dependency order for BOT-13 onward.

**Scope:** shared Tool-Bot/platform capabilities across the Work_Disk social, productivity, garment, and future government/enterprise ecosystem.

**Rule:** this inventory is a planning/architecture artifact. A listed tool is not automatically assigned a BOT number. BOT identity is locked only after repository and architecture verification.

---

## 1. Existing verified Tool-Bot foundation

| Capability | Current identity | Status |
|---|---|---|
| Delete | BOT-04 | Implemented |
| Edit | BOT-07 | Implemented |
| Search | BOT-08 | Implemented |
| Mark / Unmark | BOT-09 | Implemented |
| Filter | BOT-10 | Implemented |
| Sort By | BOT-11 | Implemented |
| Action Board | Action Board | Implemented; no BOT number assigned |

### Existing composition

```text
Search -> Filter -> Sort -> Mark/Unmark -> Action Board -> Action Tool
```

These are composable capabilities, not one monolithic action system.

---

## 2. Missing capability inventory

### A. Social/content core — highest priority

1. **Content/Post Tool** — create/read/publish content objects and lifecycle state.
2. **Feed Tool** — assemble eligible content into a feed; pagination and delivery boundaries.
3. **Social Relationship / Graph Tool** — follow, unfollow, connect, requests, relationship state.
4. **Media / Attachment Tool** — upload, acquire, process, thumbnail, metadata, lifecycle.
5. **Notification Tool** — notification creation, preference evaluation, routing and delivery state.
6. **Messaging / Chat Tool** — direct/group conversations, messages, delivery/read state.
7. **Reaction Tool** — like/reaction lifecycle.
8. **Comment / Reply Tool** — comments, replies and thread structure.
9. **Share / Repost Tool** — internal share, repost/quote semantics and attribution.
10. **Save / Bookmark Tool** — save/unsave and collections.

### B. Discovery/community

11. **Discovery / Recommendation Tool** — people, content, communities and service discovery.
12. **Topic / Hashtag Tool** — topics, follows and topic feeds.
13. **Group / Community Tool** — membership, roles, spaces and community lifecycle.

### C. Trust, safety and governance

14. **Report Tool** — user/content/message/media reporting.
15. **Block / Mute Tool** — interpersonal visibility and interaction controls.
16. **Moderation Tool** — policy evaluation, review queues, enforcement handoff.
17. **Abuse / Spam Tool** — rate/behaviour detection and abuse signals.
18. **Governance / Enforcement Tool** — restriction, suspension, quarantine, escalation, restoration.
19. **Audit / Evidence Tool** — immutable operational evidence and audit records.
20. **Consent / Privacy Tool** — consent, visibility, data-use and privacy-state controls.

### D. Government / enterprise service layer

21. **Service Request / Intake Tool** — structured citizen/customer requests.
22. **Workflow Tool** — reusable state-machine/workflow execution.
23. **Case Tool** — case lifecycle, assignment, routing, status and resolution.
24. **Form / Submission Tool** — structured forms and submissions.
25. **Document / Records Tool** — document lifecycle, versioning, retention and records.
26. **Verification Tool** — identity/entity/document verification boundary.
27. **Approval / Decision Tool** — controlled approvals, decisions and segregation-of-duties boundary.
28. **Integration / Interoperability Tool** — external government/enterprise systems and standard APIs.
29. **Eligibility / Rules Tool** — policy/rules evaluation without embedding policy in unrelated tools.
30. **Payments / Transaction Tool** — financial/service transactions where required.

### E. Platform reliability and delivery

31. **Sync / Reconciliation Tool** — offline/online synchronization and conflict/reconciliation boundaries.
32. **Event / Realtime Tool** — domain events and realtime delivery.
33. **Queue / Job Tool** — asynchronous work execution.
34. **Retry / Delivery Tool** — reliable outbound delivery and retry policy.
35. **Cache Tool** — bounded caching and invalidation.
36. **Indexing Tool** — search/filter/discovery indexing lifecycle.
37. **Health / Diagnostics Tool** — service health, diagnostics and degraded-mode evidence.
38. **Backup / Recovery Tool** — backup, restore and recovery evidence.
39. **Configuration / Feature Flag Tool** — controlled configuration and rollout state.

### F. Intelligence and analytics

40. **Analytics / Metrics Tool** — product, operational and service metrics.
41. **Ranking Tool** — reusable ranking/scoring primitives for feeds/discovery.
42. **Recommendation Tool** — personalised recommendations, separate from deterministic search/filter/sort.
43. **AI Assistant Tool** — Work_Disk guidance and capability-aware assistance.
44. **Translation / Localization Tool** — translation generation, locale selection and localisation lifecycle.

### G. Existing/planned utility tools from the broader Tool-Bot inventory

45. **ID Generator Tool** — Account, Entry, Fleet and other identifier candidates under the established ID-generation boundary.
46. **QR Generator Tool** — QR generation.
47. **Notification Generator Tool** — notification payload generation; delivery remains a separate concern.
48. **Device Permission / Access Tool** — camera/gallery/device capability access boundary.
49. **Gallery / Media Filter Tool** — media acquisition/filtering boundary where needed.
50. **Document Generation Tool** — PDF/document generation.

---

## 3. Dependency map

### Foundation

```text
Identity / Session / Authority
        |
        +-- Privacy / Consent
        +-- Verification
        +-- Audit / Evidence
        +-- Configuration
```

### Content and social

```text
Content/Post
   +-- Media
   +-- Reaction
   +-- Comment/Reply
   +-- Share/Repost
   +-- Save/Bookmark
   |
   +-- Feed

Social Graph
   +-- Feed eligibility
   +-- Discovery
   +-- Recommendations
   +-- Messaging relationships

Search
   +-- Indexing
Filter
Sort
Mark
   +-- Action Board
```

### Messaging and notifications

```text
Messaging
   +-- Media
   +-- Realtime/Event
   +-- Notification
   +-- Delivery/Retry

Domain Events
   +-- Notification
   +-- Feed invalidation
   +-- Search indexing
   +-- Moderation
   +-- Analytics
```

### Government/enterprise

```text
Service Intake
      |
      v
    Case
      |
   Workflow
      |
 +----+----+---------+
 |         |         |
Form    Document   Approval
 |         |         |
 +---------+---------+
           |
      Audit/Evidence
           |
    Integration/API
```

---

## 4. Recommended BOT-13 onward priority

The following is the **recommended sequence**, not a numerical lock. Each item must be verified against the repository and architecture before receiving a BOT number.

### Wave 1 — Social foundation

**Candidate 13: Content/Post Tool**

Reason: Feed, reactions, comments, shares and moderation need a stable content boundary.

**Candidate 14: Social Relationship / Graph Tool**

Reason: relationship state drives feed eligibility, discovery and social interactions.

**Candidate 15: Media / Attachment Tool**

Reason: social content, chat and documents need a shared media lifecycle.

**Candidate 16: Notification Tool**

Reason: many later domain events depend on notification routing/delivery.

**Candidate 17: Messaging / Chat Tool**

Reason: core social layer; depends on identity, relationships, media, realtime and notifications.

### Wave 2 — Social interaction

**Candidate 18: Reaction Tool**

**Candidate 19: Comment / Reply Tool**

**Candidate 20: Share / Repost Tool**

**Candidate 21: Save / Bookmark Tool**

**Candidate 22: Feed Tool**

Feed is intentionally after content, graph, media and core event/notification foundations.

### Wave 3 — Trust and discovery

**Candidate 23: Report Tool**

**Candidate 24: Block / Mute Tool**

**Candidate 25: Moderation Tool**

**Candidate 26: Discovery Tool**

**Candidate 27: Group / Community Tool**

### Wave 4 — Government / enterprise

**Candidate 28: Service Request / Intake Tool**

**Candidate 29: Workflow Tool**

**Candidate 30: Case Tool**

**Candidate 31: Form / Submission Tool**

**Candidate 32: Document / Records Tool**

**Candidate 33: Verification Tool**

**Candidate 34: Approval / Decision Tool**

**Candidate 35: Integration / Interoperability Tool**

**Candidate 36: Audit / Evidence Tool**

### Wave 5 — Platform infrastructure and intelligence

**Candidate 37: Sync / Reconciliation Tool**

**Candidate 38: Event / Realtime Tool**

**Candidate 39: Queue / Job Tool**

**Candidate 40: Retry / Delivery Tool**

**Candidate 41: Indexing Tool**

**Candidate 42: Health / Diagnostics Tool**

**Candidate 43: Backup / Recovery Tool**

**Candidate 44: Analytics / Metrics Tool**

**Candidate 45: Ranking Tool**

**Candidate 46: Recommendation Tool**

**Candidate 47: AI Assistant Tool**

---

## 5. Senior Pilot sequencing rules

1. **No BOT number is locked from this planning document alone.** Verify repo + architecture first.
2. **One Feature = One Folder; One Logic = One File** remains the implementation discipline.
3. A tool must have a clear authority boundary before implementation.
4. Selection, discovery, action routing and actual mutation/execution remain separate concerns.
5. Search, Filter and Sort remain read/derivation capabilities; they do not grant authority.
6. Government/enterprise tools must preserve auditability, privacy, security, interoperability and explicit workflow state.
7. Social tools must not silently become identity, permission or moderation authorities.
8. Cross-cutting infrastructure tools should be introduced only when concrete domain dependencies justify them; do not build speculative infrastructure merely because it is listed.
9. Every new Tool Bot follows:

```text
Read
-> Understand
-> Attack
-> Boundary
-> Blueprint
-> Contract
-> Roadmap
-> Repo Structure
-> Code
-> Tests
-> Docs
-> PR
-> Review
-> Merge
-> Final Verification
```

10. Final reports must distinguish **implemented**, **tested**, **merged**, **CI-verified**, and **domain-integrated** states.

---

## 6. External architecture validation

This inventory was cross-checked against current public architecture guidance. Modern social architectures commonly separate feed, social graph, notifications, moderation, media and messaging/realtime concerns. Government architecture guidance similarly treats case management, workflow, interoperability, auditability, privacy/security and reusable service capabilities as distinct concerns.

References:

- Australian Government Architecture — Case Management Standard: https://architecture.digital.gov.au/standard/case-management-standard
- Australian Government Architecture — Case Management capability: https://architecture.digital.gov.au/capability/case-management
- GOV.UK — Data and APIs reference architecture: https://www.gov.uk/guidance/develop-your-data-and-apis-using-a-reference-architecture
- Social infrastructure architecture overview: https://www.cybewave.io/example-social-app-architecture

---

## 7. Decision

**Master Tool Inventory v2 is the planning baseline for BOT-13 onward.**

It is intentionally a **capability inventory + dependency map**, not a commitment to implement all 50 items immediately.

Next step: verify the first candidate against the repository and architecture, then begin the standard attack-to-merge mission.