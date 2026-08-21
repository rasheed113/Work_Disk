#pragma once
#include <string>
namespace work_disk::tools::bot40{struct Request{std::string request_id,authority_reference,actor_reference,operation_reference;int attempt{0};};struct Result{bool accepted{false};};class Provider{public:virtual~Provider()=default;virtual Result apply(const Request&)=0;};Result execute(const Request&,Provider&);}
