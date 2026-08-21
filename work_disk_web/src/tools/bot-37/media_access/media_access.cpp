#include "media_access.h"
namespace work_disk::tools::bot37 { Result execute(const Request& r, Provider& p){ if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.media_reference.empty()) return {}; return p.apply(r); } }
