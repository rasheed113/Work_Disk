#pragma once
#include <string>
namespace work_disk::tools::bot44{enum class Operation{Create,Remove};struct Request{std::string request_id,authority_reference,actor_reference,subject_reference,relationship_reference;Operation operation;};struct Result{bool accepted{false};};class Provider{public:virtual~Provider()=default;virtual Result apply(const Request&)=0;};Result execute(const Request&,Provider&);}
