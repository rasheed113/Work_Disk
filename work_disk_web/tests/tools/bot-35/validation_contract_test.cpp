#include "../../../src/tools/bot-35/validation/validation.h"
#include <cassert>
using namespace work_disk::tools::bot35;

struct FakeProvider final : Provider {
  int calls{0};
  Result apply(const Request& request) override {
    ++calls;
    return {true, request.subject_reference};
  }
};

int main() {
  FakeProvider provider;
  Request valid{"request-1", "authority-1", "actor-1", "subject-1", "rule-1", "value-1", Operation::Validate};
  const auto accepted = execute(valid, provider);
  assert(accepted.accepted && provider.calls == 1);

  Request missing_authority = valid;
  missing_authority.authority_reference.clear();
  assert(!execute(missing_authority, provider).accepted && provider.calls == 1);

  Request missing_rule = valid;
  missing_rule.rule_reference.clear();
  assert(!execute(missing_rule, provider).accepted && provider.calls == 1);
}
