#include "cache.h"
namespace work_disk::tools::bot41{Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.key_reference.empty())return{};return p.apply(r);}}
