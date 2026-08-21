#pragma once
#include <string>
namespace work_disk::tools::bot37 {
enum class Operation { Acquire, Release };
struct Request { std::string request_id, authority_reference, actor_reference, media_reference; Operation operation; };
struct Result { bool accepted{false}; std::string access_reference; };
class Provider { public: virtual ~Provider()=default; virtual Result apply(const Request&)=0; };
Result execute(const Request&, Provider&);
}
