# Work_Disk Web — Dashboard View Mode v2.1 Boundary

View Mode owns only:
- selected presentation mode (`grid` or `list`)
- selected grid column preference (`2`, `3`, `4`)
- local persistence and validation of those preferences

View Mode does not own:
- account/profile authority
- domain services or repositories
- dashboard card definitions
- card ordering semantics
- pinning semantics
- hide/unhide semantics
- domain data lifecycle

Responsive CSS is presentation policy only. It cannot create a new semantic view mode.
