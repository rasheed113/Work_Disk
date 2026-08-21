#include "validation.h"

namespace work_disk::tools::bot35 {

Result execute(const Request& request, Provider& provider) {
  if (request.request_id.empty() || request.authority_reference.empty() ||
      request.actor_reference.empty() || request.subject_reference.empty() ||
      request.rule_reference.empty() || request.value_reference.empty()) {
    return {};
  }
  return provider.apply(request);
}

} // namespace work_disk::tools::bot35
