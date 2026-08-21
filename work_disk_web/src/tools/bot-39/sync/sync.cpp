#include "sync.h"
namespace work_disk::tools::bot39{Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.scope_reference.empty()||r.cursor_reference.empty())return{};return p.apply(r);}}
