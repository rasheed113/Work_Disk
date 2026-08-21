#include "case_workflow.h"
namespace work_disk::tools::bot31 {
Result execute(const Request& r, Provider& p) {
  if (r.request_id.empty() || r.authority_reference.empty() || r.actor_reference.empty()) return {};
  if ((r.operation == Operation::Update || r.operation == Operation::Close) && r.case_reference.empty()) return {};
  if (r.operation != Operation::Close && r.payload_reference.empty()) return {};
  return p.apply(r);
}
} // namespace work_disk::tools::bot31
