#pragma once
#include <string>
#include <vector>
namespace work_disk::tools::bot52 {
enum class Source { Camera, Gallery, DevicePicker };
struct Request { std::string request_id, caller_context; Source source; std::size_t max_candidates{1}; };
struct Result { bool accepted{false}; std::vector<std::string> media_references; };
class Provider { public: virtual ~Provider() = default; virtual Result acquire(const Request&) = 0; };
Result execute(const Request&, Provider&);
} // namespace work_disk::tools::bot52
