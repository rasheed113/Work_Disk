#include "identifier_validator_tool.h"

#include "validation/identifier_validator.h"

namespace work_disk::tools::bot01 {

bool IdentifierValidatorTool::isValid(
    IdentifierType type,
    std::string_view identifier
) {
    return IdentifierValidator::isValid(type, identifier);
}

} // namespace work_disk::tools::bot01
