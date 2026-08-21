# Account/Profile + Workspace Feature Surface — Architecture Attack

## Scope

This feature surface is the first P0 Work_Disk Web feature slice after the reusable presentation component runtime.

It establishes a real Web surface for Account/Profile context and the Workspace shell without moving domain authority into presentation code.

## Surviving architecture

`Domain services/contracts -> presentation adapters -> Account/Profile model -> Workspace shell -> reusable components`

The presentation surface receives authoritative account/profile state through an explicit typed model. It does not create, mutate, persist, authenticate, or delete account/profile records.

## Attack conclusions

- Account identity remains owned by the Account domain.
- Profile authority remains owned by the Profile domain/BOT-02.
- Workspace navigation is presentation-owned and cannot grant capabilities or permissions.
- Dashboard remains a peer feature surface reached through navigation, not a child data authority of Profile.
- Missing authoritative data renders an explicit empty state; no fabricated user/account records are introduced.
- Settings is a navigation destination boundary only in this slice; its feature implementation remains deferred.
- Visual styling uses the shared Work_Disk component system, including bright professional 3D surfaces and controlled motion.

## Non-goals

Authentication, credential handling, account mutation, profile persistence, capability activation, notification persistence, and database access are outside this presentation slice.
