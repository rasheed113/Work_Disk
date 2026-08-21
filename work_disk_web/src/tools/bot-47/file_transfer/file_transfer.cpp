#include "file_transfer.h"
namespace work_disk::tools::bot47{Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.file_reference.empty()||r.scope_reference.empty())return{};return p.apply(r);}}
