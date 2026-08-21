#include "../../../src/tools/bot-31/case_workflow/case_workflow.h"
#include <cassert>
using namespace work_disk::tools::bot31;
struct FakeProvider final : Provider { int calls{0}; Result apply(const Request& r) override { ++calls; return {true, r.case_reference.empty() ? r.request_id : r.case_reference}; } };
int main() {
  FakeProvider p;
  Request open{"r1","auth","actor","","payload",Operation::Open};
  assert(execute(open,p).accepted && p.calls == 1);
  Request bad = open; bad.authority_reference.clear();
  assert(!execute(bad,p).accepted && p.calls == 1);
  Request update{"r2","auth","actor","case1","payload",Operation::Update};
  assert(execute(update,p).accepted && p.calls == 2);
  Request close{"r3","auth","actor","case1","",Operation::Close};
  assert(execute(close,p).accepted && p.calls == 3);
}
