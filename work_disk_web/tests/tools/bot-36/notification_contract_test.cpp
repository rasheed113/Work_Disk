#include "../../../src/tools/bot-36/notification/notification.h"
#include <cassert>
using namespace work_disk::tools::bot36;
struct FakeProvider final : Provider { int calls{0}; Result apply(const Request& r) override { ++calls; return {true,r.recipient_reference}; } };
int main(){ FakeProvider p; Request ok{"r1","a1","u1","u2","payload",Operation::Create}; assert(execute(ok,p).accepted&&p.calls==1); Request bad=ok; bad.recipient_reference.clear(); assert(!execute(bad,p).accepted&&p.calls==1); }
