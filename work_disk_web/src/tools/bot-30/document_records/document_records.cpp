#include "document_records.h"
namespace work_disk::tools::bot30 {
Result execute(const Request& r, Provider& p) {
  if (r.request_id.empty() || r.authority_reference.empty() || r.actor_reference.empty()) return {};
  if ((r.operation == Operation::Create || r.operation == Operation::Update) && r.payload_reference.empty()) return {};
  if (r.operation != Operation::Create && r.record_reference.empty()) return {};
  return p.apply(r);
}
} // namespace work_disk::tools::bot30
