# BOT-54 — i18n / Translation Tool

BOT-54 validates translation resource requests and delegates translation to a provider. It preserves stable resource keys and does not own UI rendering, user locale authority or locale policy.

When source and target languages are identical, the source text is returned unchanged; no translation provider call is required.

Contract tests use a provider double to verify validation, delegation and the identity-language path. No production translation output is hardcoded as a provider result.
