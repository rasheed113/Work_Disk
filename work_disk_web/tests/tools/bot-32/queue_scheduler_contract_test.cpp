#include "../../../src/tools/bot-32/queue_scheduler/queue_scheduler.h"
#include <cassert>
using namespace work_disk::tools::bot32;
struct FakeProvider final : Provider { int calls{0}; Result apply(const Request& r) override { ++calls; return {true,r.task_reference}; } };
int main(){ FakeProvider p; Request ok{"r1","auth","actor","task",Operation::Enqueue}; assert(execute(ok,p).accepted&&p.calls==1); Request bad=ok; bad.authority_reference.clear(); assert(!execute(bad,p).accepted&&p.calls==1); }
