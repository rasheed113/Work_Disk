#pragma once
#include <string>
namespace work_disk::tools::bot46{enum class Operation{Send,Withdraw};struct Request{std::string request_id,authority_reference,actor_reference,conversation_reference,payload_reference;Operation operation;};struct Result{bool accepted{false};};class Provider{public:virtual~Provider()=default;virtual Result apply(const Request&)=0;};Result execute(const Request&,Provider&);}
