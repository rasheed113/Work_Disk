#pragma once
#include <string>
namespace work_disk::tools::bot54 {
struct Request { std::string request_id, caller_context, source_language, target_language, resource_key, source_text; };
struct Result { bool accepted{false}; std::string translated_text; };
class Provider { public: virtual ~Provider() = default; virtual Result translate(const Request&) = 0; };
Result execute(const Request&, Provider&);
} // namespace work_disk::tools::bot54
