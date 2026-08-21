#pragma once
#include <cstdint>
#include <string>
namespace work_disk::tools::share { struct ShareRequest { std::string request_id, authority_reference, actor_reference, target_reference, destination_reference, mode; std::uint64_t expected_version{0}; }; struct ShareResult { bool accepted{false}; std::string error; }; }
