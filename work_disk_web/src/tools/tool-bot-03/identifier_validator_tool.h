#pragma once

#include "types/identifier_type.h"

#include <string_view>

namespace work_disk::tools::bot03 {

class IdentifierValidatorTool {
public:
    static bool isValid(
        IdentifierType type,
        std::string_view identifier
    );
};

} // namespace work_disk::tools::bot03
