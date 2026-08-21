#pragma once
#include <string>
namespace work_disk::tools::bot43{struct Request{std::string request_id,authority_reference,actor_reference,scope_reference,payload_reference;};struct Result{bool accepted{false};};class Provider{public:virtual~Provider()=default;virtual Result apply(const Request&)=0;};Result execute(const Request&,Provider&);}
