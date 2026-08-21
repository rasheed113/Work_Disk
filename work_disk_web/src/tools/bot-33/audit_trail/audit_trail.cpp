#include "audit_trail.h"

namespace work_disk::tools::bot33 {

Result execute(const Event& e, Provider& provider) {
  if (e.event_id.empty() || e.request_id.empty() ||
      e.authority_reference.empty() || e.actor_reference.empty() ||
      e.subject_reference.empty() || e.event_type.empty() ||
      e.evidence_reference.empty() || e.occurred_at <= 0 || e.sequence < 0) {
    return {};
  }
  return provider.append(e);
}

} // namespace work_disk::tools::bot33
