#pragma once

#include "tool_bot_03_result.h"
#include "types/identifier_type.h"

namespace work_disk::tools::bot03 {

class IdentifierGeneratorTool {
public:
    static IdentifierGenerationResult generate(IdentifierType type);
};

} // namespace work_disk::tools::bot03
