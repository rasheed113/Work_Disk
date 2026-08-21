#include "permission.h"
namespace work_disk::tools::bot38 { Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.subject_reference.empty()||r.capability_reference.empty())return{};return p.apply(r);} }
