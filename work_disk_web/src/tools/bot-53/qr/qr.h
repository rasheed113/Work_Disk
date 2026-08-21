#pragma once
#include <string>
namespace work_disk::tools::bot53 {
struct EncodeRequest { std::string request_id, caller_context, envelope_type, version, payload; };
struct DecodeRequest { std::string request_id, caller_context, encoded; };
struct Result { bool accepted{false}; std::string value; };
class Provider { public: virtual ~Provider() = default; virtual Result encode(const EncodeRequest&) = 0; virtual Result decode(const DecodeRequest&) = 0; };
Result encode(const EncodeRequest&, Provider&);
Result decode(const DecodeRequest&, Provider&);
} // namespace work_disk::tools::bot53
