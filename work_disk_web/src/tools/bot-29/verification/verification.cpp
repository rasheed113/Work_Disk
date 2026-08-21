#include "verification.h"
namespace work_disk::tools::bot29 {
Result execute(const Request& r, Provider& p) {
  if (r.request_id.empty() || r.authority_reference.empty() ||
      r.subject_reference.empty() || r.evidence_reference.empty()) return {};
  return p.apply(r);
}
} // namespace work_disk::tools::bot29
