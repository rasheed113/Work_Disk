#include "secure_random.h"

#include <cerrno>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string>

namespace work_disk::tools::bot01 {

std::vector<std::uint8_t> SecureRandom::bytes(std::size_t count) {
    if (count == 0) {
        return {};
    }

    std::vector<std::uint8_t> result(count);

    std::ifstream random_source("/dev/urandom", std::ios::in | std::ios::binary);

    if (!random_source) {
        throw std::runtime_error(
            std::string("Unable to open secure randomness source: ") +
            std::strerror(errno)
        );
    }

    random_source.read(
        reinterpret_cast<char*>(result.data()),
        static_cast<std::streamsize>(result.size())
    );

    if (!random_source) {
        throw std::runtime_error(
            std::string("Unable to obtain secure random bytes: ") +
            std::strerror(errno)
        );
    }

    return result;
}

} // namespace work_disk::tools::bot01
