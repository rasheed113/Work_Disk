#include "identifier_generator_tool.h"

#include "generator/identifier_generator.h"

namespace work_disk::tools::bot01 {

std::string IdentifierGeneratorTool::generate(IdentifierType type) {
    return IdentifierGenerator::generate(type);
}

} // namespace work_disk::tools::bot01
