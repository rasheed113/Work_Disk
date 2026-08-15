#pragma once

#include "tool_bot_01_result.h"
#include "types/identifier_type.h"

namespace work_disk::tools::bot01 {

class IdentifierGeneratorTool {
public:
    static IdentifierGenerationResult generate(IdentifierType type);
};

} // namespace work_disk::tools::bot01
