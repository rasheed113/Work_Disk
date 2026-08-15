#include "identifier_policy.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::bot03;

int main() {
    assert(
        IdentifierPolicy::length(IdentifierType::Account) == 9
    );

    assert(
        IdentifierPolicy::length(IdentifierType::Entry) == 11
    );

    assert(
        IdentifierPolicy::length(IdentifierType::Fleet) == 7
    );

    std::cout << "IDENTIFIER_POLICY_TEST=PASS\n";

    return 0;
}
