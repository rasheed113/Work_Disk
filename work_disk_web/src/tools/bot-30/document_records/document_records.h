#pragma once
#include <string>
namespace work_disk::tools::bot30 {
enum class Operation { Create, Update, Archive, Restore };
struct Request { std::string request_id; std::string authority_reference; std::string actor_reference; std::string record_reference; std::string payload_reference; Operation operation; };
struct Result { bool accepted{false}; std::string record_reference; };
class Provider { public: virtual ~Provider() = default; virtual Result apply(const Request&) = 0; };
Result execute(const Request&, Provider&);
} // namespace work_disk::tools::bot30
