#include "relationship.h"
namespace work_disk::tools::bot44{Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.subject_reference.empty()||r.relationship_reference.empty())return{};return p.apply(r);}}
