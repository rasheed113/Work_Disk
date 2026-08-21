#include "retry_recovery.h"
namespace work_disk::tools::bot40{Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.operation_reference.empty()||r.attempt<0)return{};return p.apply(r);}}
