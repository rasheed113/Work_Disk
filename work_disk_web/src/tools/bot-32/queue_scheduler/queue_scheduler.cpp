#include "queue_scheduler.h"
namespace work_disk::tools::bot32 {
Result execute(const Request& r, Provider& p) {
  if (r.request_id.empty() || r.authority_reference.empty() || r.actor_reference.empty() || r.task_reference.empty()) return {};
  return p.apply(r);
}
} // namespace work_disk::tools::bot32
