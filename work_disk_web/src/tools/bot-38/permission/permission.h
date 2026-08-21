#pragma once
#include <string>
namespace work_disk::tools::bot38 { enum class Operation{Grant,Revoke}; struct Request{std::string request_id,authority_reference,actor_reference,subject_reference,capability_reference;Operation operation;}; struct Result{bool accepted{false};}; class Provider{public:virtual~Provider()=default;virtual Result apply(const Request&)=0;}; Result execute(const Request&,Provider&); }
