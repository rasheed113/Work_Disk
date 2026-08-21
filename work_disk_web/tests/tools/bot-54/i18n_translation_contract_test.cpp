#include "../../../src/tools/bot-54/i18n_translation/i18n_translation.h"
#include <cassert>
using namespace work_disk::tools::bot54;
struct FakeProvider final : Provider { int calls{0}; Result translate(const Request& r) override { ++calls; return {true,r.source_text + "|translated-by-provider"}; } };
int main(){ FakeProvider p; Request ok{"r1","caller1","en","ur","dashboard.title","Dashboard"}; auto result=execute(ok,p); assert(result.accepted&&p.calls==1&&result.translated_text=="Dashboard|translated-by-provider"); Request same=ok; same.target_language="en"; auto identity=execute(same,p); assert(identity.accepted&&identity.translated_text=="Dashboard"&&p.calls==1); Request bad=ok; bad.resource_key.clear(); assert(!execute(bad,p).accepted&&p.calls==1); }
