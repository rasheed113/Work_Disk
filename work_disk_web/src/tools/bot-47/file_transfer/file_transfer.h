#pragma once
#include <string>
namespace work_disk::tools::bot47{enum class Operation{Upload,Download};struct Request{std::string request_id,authority_reference,actor_reference,file_reference,scope_reference;Operation operation;};struct Result{bool accepted{false};};class Provider{public:virtual~Provider()=default;virtual Result apply(const Request&)=0;};Result execute(const Request&,Provider&);}
