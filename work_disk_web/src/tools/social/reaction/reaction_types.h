#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace work_disk::tools::reaction {
struct ReactionRequest { std::string request_id; std::string authority_reference; std::string actor_reference; std::string target_reference; std::string reaction_type; std::uint64_t expected_version{0}; };
struct ReactionResult { bool accepted{false}; std::string error; };
}
