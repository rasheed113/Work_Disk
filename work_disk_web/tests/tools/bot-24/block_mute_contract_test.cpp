#include "../../../src/tools/bot-24/block_mute.h"
#include <cassert>

using namespace work_disk::tools::bot24;

struct FakeProvider final : Provider {
  int calls{0};
  Result apply(const Request& request) override {
    ++calls;
    return {true, request.target_reference};
  }
};

int main() {
  FakeProvider provider;
  Request valid{"r1", "auth", "actor", "target", Operation::Block, -1};
  auto accepted = execute(valid, provider);
  assert(accepted.accepted);
  assert(provider.calls == 1);

  Request missing = valid;
  missing.authority_reference.clear();
  auto rejected = execute(missing, provider);
  assert(!rejected.accepted);
  assert(provider.calls == 1);

  Request self = valid;
  self.target_reference = self.actor_reference;
  auto self_rejected = execute(self, provider);
  assert(!self_rejected.accepted);
  assert(provider.calls == 1);
}
