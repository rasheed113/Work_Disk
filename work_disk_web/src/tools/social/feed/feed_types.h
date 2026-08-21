#pragma once
#include <cstdint>
#include <string>
#include <vector>
namespace work_disk::tools::feed { struct FeedRequest { std::string request_id, authority_reference, viewer_reference, scope_reference, cursor; std::uint32_t limit{20}; }; struct FeedItem { std::string target_reference; std::uint64_t rank_key{0}; }; struct FeedResult { bool accepted{false}; std::string error; std::vector<FeedItem> items; std::string next_cursor; }; }
