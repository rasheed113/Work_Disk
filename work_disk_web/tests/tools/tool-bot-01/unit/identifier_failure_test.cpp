#include "identifier_generator.h"
#include "identifier_policy.h"
#include "identifier_validator.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

using namespace work_disk::tools::bot01;

int main() {
    const auto invalid_type =
        static_cast<IdentifierType>(999);

    bool generator_threw = false;

    try {
        (void)IdentifierGenerator::generate(invalid_type);
    } catch (const std::invalid_argument&) {
        generator_threw = true;
    }

    assert(generator_threw);

    bool policy_length_threw = false;

    try {
        (void)IdentifierPolicy::length(invalid_type);
    } catch (const std::invalid_argument&) {
        policy_length_threw = true;
    }

    assert(policy_length_threw);

    assert(
        !IdentifierValidator::isValid(
            invalid_type,
            "anything"
        )
    );

    std::cout << "IDENTIFIER_FAILURE_TEST=PASS\n";

    return 0;
}
