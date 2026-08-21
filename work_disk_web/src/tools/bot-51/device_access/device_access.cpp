#include "device_access.h"

namespace work_disk::tools::bot51 {

namespace {
bool valid(Capability capability) {
  switch (capability) {
    case Capability::Camera:
    case Capability::Microphone:
    case Capability::Location:
    case Capability::MediaLibrary:
      return true;
  }
  return false;
}
}

Result execute(const Request& request, Provider& provider) {
  if (request.request_id.empty() || request.caller_context.empty() ||
      !valid(request.capability)) {
    return {};
  }

  if (request.operation == Operation::Request) {
    return provider.request(request);
  }
  return provider.observe(request);
}

} // namespace work_disk::tools::bot51
