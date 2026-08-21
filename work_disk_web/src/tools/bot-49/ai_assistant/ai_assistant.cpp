#include "ai_assistant.h"
namespace work_disk::tools::bot49{Result execute(const Request&r,Provider&p){if(r.request_id.empty()||r.authority_reference.empty()||r.actor_reference.empty()||r.context_reference.empty()||r.prompt_reference.empty())return{};return p.apply(r);}}
