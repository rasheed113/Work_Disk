#include "notification.h"
namespace work_disk::tools::bot36 {
Result execute(const Request& r, Provider& p) {
  if (r.request_id.empty() || r.authority_reference.empty() || r.actor_reference.empty() || r.recipient_reference.empty()) return {};
  if (r.operation == Operation::Create && r.payload_reference.empty()) return {};
  return p.apply(r);
}
} // namespace work_disk::tools::bot36
