#pragma once
#include <string>
namespace work_disk::tools::bot49{struct Request{std::string request_id,authority_reference,actor_reference,context_reference,prompt_reference;};struct Result{bool accepted{false};};class Provider{public:virtual~Provider()=default;virtual Result apply(const Request&)=0;};Result execute(const Request&,Provider&);}
