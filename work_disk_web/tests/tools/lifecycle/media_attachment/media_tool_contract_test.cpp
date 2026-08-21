#include "../../../../src/tools/lifecycle/media_attachment/media_tool.h"
#include <cassert>
using namespace work_disk::tools::media_attachment;
struct Authority final : MediaAuthority { bool allowed{true}; bool may_apply(const MediaCommand&) const override { return allowed; } };
struct Provider final : MediaProvider { int calls{0}; MediaResult apply(const MediaCommand&) override { ++calls; return {MediaResultCode::Applied, "opaque-attachment"}; } };
MediaCommand cmd() { return {"req","auth","scope","owner","media",MediaOperation::Attach,"idem","v1"}; }
int main() { Authority a; Provider p; MediaTool t(a,p); auto r=t.handle(cmd()); assert(r.code==MediaResultCode::Applied); assert(p.calls==1); a.allowed=false; auto x=t.handle(cmd()); assert(x.code==MediaResultCode::AuthorityRejected); assert(p.calls==1); return 0; }
