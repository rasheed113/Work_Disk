#pragma once
#include <string>
namespace work_disk::tools::bot36 {
enum class Operation { Create, Cancel };
struct Request { std::string request_id, authority_reference, actor_reference, recipient_reference, payload_reference; Operation operation; };
struct Result { bool accepted{false}; std::string notification_reference; };
class Provider { public: virtual ~Provider() = default; virtual Result apply(const Request&) = 0; };
Result execute(const Request&, Provider&);
} // namespace work_disk::tools::bot36
