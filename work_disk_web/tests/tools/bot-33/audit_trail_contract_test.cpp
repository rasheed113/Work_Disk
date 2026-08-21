#include "../../../src/tools/bot-33/audit_trail/audit_trail.h"
#include <cassert>
#include <chrono>
#include <string>

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
  const auto now = std::chrono::system_clock::now().time_since_epoch().count();
  const auto token = std::to_string(now);
  ContractProvider provider;
  Event valid{token, token + ":request", token + ":authority", token + ":actor",
              token + ":subject", token + ":event", token + ":evidence", 1, 0};

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
