#include "identifier_validator.h"

#include <cassert>
#include <iostream>
#include <string>

using namespace work_disk::tools::bot01;

int main() {
    // Valid identifiers.
    assert(
        IdentifierValidator::isValid(
            IdentifierType::Account,
            "324a6K8Xq"
        )
    );

    assert(
        IdentifierValidator::isValid(
            IdentifierType::Entry,
            "A7k92Lm4QxZ"
        )
    );

    assert(
        IdentifierValidator::isValid(
            IdentifierType::Fleet,
            "F7k2Lm9"
        )
    );

    // Wrong lengths.
    assert(
        !IdentifierValidator::isValid(
            IdentifierType::Account,
            "324a6K8"
        )
    );

    assert(
        !IdentifierValidator::isValid(
            IdentifierType::Entry,
            "A7k92Lm4"
        )
    );

    assert(
        !IdentifierValidator::isValid(
            IdentifierType::Fleet,
            "F7k2"
        )
    );

    // Special characters are forbidden.
    assert(
        !IdentifierValidator::isValid(
            IdentifierType::Account,
            "324a6K8$!"
        )
    );

    // Empty identifier is invalid.
    assert(
        !IdentifierValidator::isValid(
            IdentifierType::Entry,
            ""
        )
    );

    std::cout << "IDENTIFIER_VALIDATOR_TEST=PASS\n";

    return 0;
}
