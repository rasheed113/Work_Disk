#pragma once
#include <cstdint>
#include <string>
namespace work_disk::tools::bookmark { struct BookmarkRequest { std::string request_id, authority_reference, actor_reference, target_reference, collection_reference; std::uint64_t expected_version{0}; }; struct BookmarkResult { bool accepted{false}; std::string error; }; }
