#pragma once
#include <string>
namespace work_disk::tools::bot32 {
enum class Operation { Enqueue, Cancel };
struct Request { std::string request_id, authority_reference, actor_reference, task_reference; Operation operation; };
struct Result { bool accepted{false}; std::string queue_reference; };
class Provider { public: virtual ~Provider() = default; virtual Result apply(const Request&) = 0; };
Result execute(const Request&, Provider&);
} // namespace work_disk::tools::bot32
