#include "identifier_policy.h"

#include <stdexcept>

namespace work_disk::tools::bot01 {

std::size_t IdentifierPolicy::length(IdentifierType type) {
    switch (type) {
        case IdentifierType::Account:
            return 9;

        case IdentifierType::Entry:
            return 11;

        case IdentifierType::Fleet:
            return 7;
    }

    throw std::invalid_argument("Unknown identifier type");
}


} // namespace work_disk::tools::bot01
