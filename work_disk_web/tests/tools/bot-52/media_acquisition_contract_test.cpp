#include "../../../src/tools/bot-52/media_acquisition/media_acquisition.h"
#include <cassert>
using namespace work_disk::tools::bot52;
struct FakeProvider final : Provider { int calls{0}; Result acquire(const Request& r) override { ++calls; return {true,{"candidate-from-provider"}}; } };
int main(){ FakeProvider p; Request ok{"r1","caller1",Source::Gallery,3}; auto result=execute(ok,p); assert(result.accepted&&p.calls==1&&result.media_references.size()==1); Request bad=ok; bad.caller_context.clear(); assert(!execute(bad,p).accepted&&p.calls==1); Request zero=ok; zero.max_candidates=0; assert(!execute(zero,p).accepted&&p.calls==1); }
