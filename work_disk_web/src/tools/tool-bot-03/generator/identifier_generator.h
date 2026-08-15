#pragma once

#include "../types/identifier_type.h"

#include <string>

namespace work_disk::tools::bot03 {

class IdentifierGenerator {
public:
    static std::string generate(IdentifierType type);
};

} // namespace work_disk::tools::bot03
