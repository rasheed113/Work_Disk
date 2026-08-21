#include "../../../src/tools/bot-51/device_access/device_access.h"
#include <cassert>
using namespace work_disk::tools::bot51;

struct FakeProvider final : Provider {
  int request_calls{0};
  int observe_calls{0};
  Result request(const Request&) override { ++request_calls; return {true, AccessState::Denied}; }
  Result observe(const Request&) override { ++observe_calls; return {true, AccessState::Granted}; }
};

int main() {
  FakeProvider provider;
  Request request{"req-1", "caller-1", Capability::Camera, Operation::Request};
  auto denied = execute(request, provider);
  assert(denied.accepted && denied.state == AccessState::Denied && provider.request_calls == 1);

  Request observation{"req-2", "caller-1", Capability::Camera, Operation::Observe};
  auto granted = execute(observation, provider);
  assert(granted.accepted && granted.state == AccessState::Granted && provider.observe_calls == 1);

  Request missing_context = request;
  missing_context.caller_context.clear();
  assert(!execute(missing_context, provider).accepted && provider.request_calls == 1);
}
