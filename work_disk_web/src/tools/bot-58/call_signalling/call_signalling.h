#pragma once
#include <string>
namespace work_disk::tools::bot58 { struct Request{std::string request_id,caller_context,session_reference,signal;}; struct Result{bool accepted{false};}; class Provider{public:virtual~Provider()=default;virtual Result signal(const Request&)=0;}; Result execute(const Request&,Provider&); }