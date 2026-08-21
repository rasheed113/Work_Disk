#include "moderation.h"
namespace work_disk::tools::bot25 {
Result execute(const Request& r, Provider& p) {
 if(r.request_id.empty()||r.authority_reference.empty()||r.moderator_reference.empty()||r.target_reference.empty()||r.policy_reference.empty()||r.action_reference.empty()) return {};
 return p.moderate(r);
}
}