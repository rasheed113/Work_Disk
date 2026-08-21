#pragma once
#include <cstdint>
#include <string>
namespace work_disk::tools::comment { struct CommentRequest { std::string request_id, authority_reference, actor_reference, target_reference, body; std::uint64_t expected_version{0}; }; struct CommentResult { bool accepted{false}; std::string error; }; }
