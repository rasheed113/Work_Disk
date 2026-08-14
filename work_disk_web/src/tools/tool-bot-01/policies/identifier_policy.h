#pragma once

#include "../types/identifier_type.h"

#include <cstddef>

namespace work_disk::tools::bot01 {

enum class GenerationMode {
    OnlineOnly,
    Hybrid
};

class IdentifierPolicy {
public:
    static std::size_t length(IdentifierType type);
    static GenerationMode generationMode(IdentifierType type);
};

} // namespace work_disk::tools::bot01
