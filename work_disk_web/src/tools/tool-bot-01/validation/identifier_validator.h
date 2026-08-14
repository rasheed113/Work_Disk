#pragma once

#include "../types/identifier_type.h"

#include <string_view>

namespace work_disk::tools::bot01 {

class IdentifierValidator {
public:
    static bool isValid(
        IdentifierType type,
        std::string_view identifier
    );
};

} // namespace work_disk::tools::bot01
