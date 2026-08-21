#include "groups_community.h"
namespace work_disk::tools::bot27 {
Result execute(const Request& r, Provider& p) {
  if (r.request_id.empty() || r.authority_reference.empty() || r.actor_reference.empty() || r.community_reference.empty()) return {};
  if (r.operation != Operation::Create && r.operation != Operation::Join && r.operation != Operation::Leave) return {};
  return p.apply(r);
}
}
