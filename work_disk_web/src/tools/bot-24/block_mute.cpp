#include "block_mute.h"

namespace work_disk::tools::bot24 {

Result execute(const Request& request, Provider& provider) {
  if (request.request_id.empty() || request.authority_reference.empty() ||
      request.actor_reference.empty() || request.target_reference.empty()) {
    return {};
  }
  if (request.actor_reference == request.target_reference) {
    return {};
  }
  if (request.expected_version < -1) {
    return {};
  }
  return provider.apply(request);
}

} // namespace work_disk::tools::bot24
