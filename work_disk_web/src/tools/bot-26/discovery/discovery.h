#pragma once
#include <string>
#include <vector>
namespace work_disk::tools::bot26 {
struct Request { std::string request_id, authority_reference, actor_reference, query; std::size_t limit{20}; };
struct Result { bool accepted{false}; std::vector<std::string> references; };
class Provider { public: virtual ~Provider() = default; virtual Result discover(const Request&) = 0; };
Result execute(const Request&, Provider&);
}
