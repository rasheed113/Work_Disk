# BOT-11 — Integration

Recommended composition:

Search (BOT-08) → Filter (BOT-10) → Sort By (BOT-11) → Mark/Unmark (BOT-09) → action tools.

BOT-11 can also be called directly by any authorised page/domain that already has a result scope.

The caller owns authority and domain field mapping. The provider owns concrete ordering semantics, including collation and size-unit interpretation. Action tools must not treat a sorted result as an authority grant.
