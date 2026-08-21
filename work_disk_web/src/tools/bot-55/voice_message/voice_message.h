#pragma once
#include <string>
namespace work_disk::tools::bot55 {
struct Request { std::string request_id, caller_context, media_reference; };
struct Result { bool accepted{false}; std::string message_reference; };
class Provider { public: virtual ~Provider()=default; virtual Result send(const Request&)=0; };
Result execute(const Request&, Provider&);
}