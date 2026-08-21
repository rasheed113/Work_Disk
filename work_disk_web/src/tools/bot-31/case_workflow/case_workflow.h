#pragma once
#include <string>
namespace work_disk::tools::bot31 {
enum class Operation { Open, Update, Close };
struct Request { std::string request_id, authority_reference, actor_reference, case_reference, payload_reference; Operation operation; };
struct Result { bool accepted{false}; std::string workflow_reference; };
class Provider { public: virtual ~Provider() = default; virtual Result apply(const Request&) = 0; };
Result execute(const Request&, Provider&);
} // namespace work_disk::tools::bot31
