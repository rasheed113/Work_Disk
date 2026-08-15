#include "identifier_validator.h"

#include "../generator/identifier_alphabet.h"
#include "../policies/identifier_policy.h"

#include <stdexcept>

namespace work_disk::tools::bot03 {

bool IdentifierValidator::isValid(
    IdentifierType type,
    std::string_view identifier
) {
    try {
        if (identifier.size() != IdentifierPolicy::length(type)) {
            return false;
        }
    } catch (const std::invalid_argument&) {
        return false;
    }

    const std::string_view alphabet = IdentifierAlphabet::value();

    for (const char character : identifier) {
        if (alphabet.find(character) == std::string_view::npos) {
            return false;
        }
    }

    return true;
}

} // namespace work_disk::tools::bot03
