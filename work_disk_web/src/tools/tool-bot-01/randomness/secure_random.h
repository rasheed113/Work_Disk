#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace work_disk::tools::bot01 {

class SecureRandom {
public:
    static std::vector<std::uint8_t> bytes(std::size_t count);
};

} // namespace work_disk::tools::bot01
