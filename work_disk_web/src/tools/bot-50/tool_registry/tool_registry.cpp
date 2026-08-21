#include "tool_registry.h"
namespace work_disk::tools::bot50{Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.tool_reference.empty()||r.operation_reference.empty())return{};return p.dispatch(r);}}
