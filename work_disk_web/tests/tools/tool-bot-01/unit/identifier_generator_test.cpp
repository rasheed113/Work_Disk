#include "identifier_generator.h"

#include <cassert>
#include <cctype>
#include <iostream>
#include <set>
#include <string>

using namespace work_disk::tools::bot01;

static void verify_identifier(
    IdentifierType type,
    std::size_t expected_length
) {
    const std::string id = IdentifierGenerator::generate(type);

    assert(id.size() == expected_length);

    for (const unsigned char character : id) {
        assert(std::isalnum(character) != 0);
    }
}

int main() {
    verify_identifier(IdentifierType::Account, 9);
    verify_identifier(IdentifierType::Entry, 11);
    verify_identifier(IdentifierType::Fleet, 7);

    std::set<std::string> generated;

    for (int i = 0; i < 100; ++i) {
        generated.insert(
            IdentifierGenerator::generate(IdentifierType::Entry)
        );
    }

    assert(!generated.empty());

    std::cout << "IDENTIFIER_GENERATOR_TEST=PASS\n";

    return 0;
}
