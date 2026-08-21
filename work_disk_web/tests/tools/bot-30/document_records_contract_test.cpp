#include "../../../src/tools/bot-30/document_records/document_records.h"
#include <cassert>
using namespace work_disk::tools::bot30;
struct FakeProvider final : Provider { int calls{0}; Result apply(const Request& r) override { ++calls; return {true,r.record_reference}; } };
int main() {
  FakeProvider p;
  Request create{"r1","auth","actor","","payload",Operation::Create};
  assert(execute(create,p).accepted && p.calls == 1);
  Request bad=create; bad.authority_reference.clear();
  assert(!execute(bad,p).accepted && p.calls == 1);
  Request update=create; update.operation=Operation::Update; update.record_reference="rec"; update.payload_reference.clear();
  assert(!execute(update,p).accepted && p.calls == 1);
}
