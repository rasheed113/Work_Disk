#include "identifier_generator_tool.h"

#include "generator/identifier_generator.h"

#include <stdexcept>

namespace work_disk::tools::bot03 {

IdentifierGenerationResult IdentifierGeneratorTool::generate(
    IdentifierType type
) {
    try {
        return IdentifierGenerationResult::success(
            IdentifierGenerator::generate(type)
        );
    } catch (const std::invalid_argument&) {
        return IdentifierGenerationResult::failure(
            ToolBot03Error::InvalidIdentifierType
        );
    } catch (const std::runtime_error&) {
        return IdentifierGenerationResult::failure(
            ToolBot03Error::RandomnessUnavailable
        );
    }
}

} // namespace work_disk::tools::bot03
