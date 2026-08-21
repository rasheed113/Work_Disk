#include "discovery.h"
namespace work_disk::tools::bot26 {
Result execute(const Request& r, Provider& p) {
  if (r.request_id.empty() || r.authority_reference.empty() || r.actor_reference.empty() || r.query.empty() || r.limit == 0 || r.limit > 100) return {};
  return p.discover(r);
}
}
