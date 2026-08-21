#pragma once
#include <string>
namespace work_disk::tools::bot50{struct Request{std::string request_id,authority_reference,actor_reference,tool_reference,operation_reference;};struct Result{bool accepted{false};};class Provider{public:virtual~Provider()=default;virtual Result dispatch(const Request&)=0;};Result execute(const Request&,Provider&);}
