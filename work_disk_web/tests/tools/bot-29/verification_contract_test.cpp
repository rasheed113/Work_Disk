#include "../../../src/tools/bot-29/verification/verification.h"
#include <cassert>
using namespace work_disk::tools::bot29;
struct FakeProvider final : Provider { int calls{0}; Result apply(const Request& r) override { ++calls; return {true,r.subject_reference}; } };
int main() {
  FakeProvider p;
  Request valid{"r1","auth","subject","evidence",Operation::Verify};
  assert(execute(valid,p).accepted && p.calls == 1);
  Request missing = valid; missing.evidence_reference.clear();
  assert(!execute(missing,p).accepted && p.calls == 1);
}
