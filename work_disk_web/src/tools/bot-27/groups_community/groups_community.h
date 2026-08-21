#pragma once
#include <string>
namespace work_disk::tools::bot27 {
enum class Operation { Create, Join, Leave };
struct Request { std::string request_id, authority_reference, actor_reference, community_reference; Operation operation; };
struct Result { bool accepted{false}; std::string membership_reference; };
class Provider { public: virtual ~Provider()=default; virtual Result apply(const Request&)=0; };
Result execute(const Request&, Provider&);
}
