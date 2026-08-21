#pragma once

#include <chrono>
#include <string>

namespace work_disk::tools::lifecycle::trash_tool {

using TrashTime = std::chrono::system_clock::time_point;

struct TrashEntry {
    std::string itemId;
    std::string targetType;
    std::string targetId;
    std::string originalLocationReference;
    std::string payloadReference;
    TrashTime deletedAt{};
    TrashTime expiresAt{};
};

struct TrashEntryInput {
    std::string itemId;
    std::string targetType;
    std::string targetId;
    std::string originalLocationReference;
    std::string payloadReference;
    TrashTime deletedAt{};
};

struct TrashAuthority {
    std::string authorityReference;
};

} // namespace work_disk::tools::lifecycle::trash_tool
