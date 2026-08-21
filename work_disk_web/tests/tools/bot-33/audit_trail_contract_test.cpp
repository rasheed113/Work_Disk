#include "../../../src/tools/bot-33/audit_trail/audit_trail.h"
#include <cassert>

using namespace work_disk::tools::bot33;

class ContractProvider final : public Provider {
 public:
  bool called{false};
  Result append(const Event& event) override {
    called = true;
    assert(!event.event_id.empty());
    assert(!event.evidence_reference.empty());
    return {true, event.event_id};
  }
};

int main() {
  ContractProvider provider;
  Event valid{"event-1", "request-1", "authority-1", "actor-1", "subject-1",
              "profile.updated", "evidence-1", 1700000000, 0};
  const auto accepted = execute(valid, provider);
  assert(accepted.accepted);
  assert(provider.called);

  provider.called = false;
  Event missing_authority = valid;
  missing_authority.authority_reference.clear();
  const auto rejected = execute(missing_authority, provider);
  assert(!rejected.accepted);
  assert(!provider.called);
}
