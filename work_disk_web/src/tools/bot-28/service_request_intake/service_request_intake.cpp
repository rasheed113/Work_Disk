#include "service_request_intake.h"
namespace work_disk::tools::bot28 {
Result execute(const Request& request, Provider& provider) {
  if (request.request_id.empty() || request.authority_reference.empty() || request.actor_reference.empty() || request.service_reference.empty()) return {};
  if (request.operation == Operation::Submit && request.payload_reference.empty()) return {};
  return provider.apply(request);
}
}
