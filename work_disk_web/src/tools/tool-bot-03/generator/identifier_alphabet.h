#pragma once

#include <string_view>

namespace work_disk::tools::bot03 {

class IdentifierAlphabet {
public:
    static constexpr std::string_view value() noexcept {
        return "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
               "abcdefghijklmnopqrstuvwxyz"
               "0123456789";
    }
};

} // namespace work_disk::tools::bot03
