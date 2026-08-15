#include "identifier_generator.h"
#include "generator/identifier_alphabet.h"

#include <cassert>
#include <cctype>
#include <iostream>
#include <set>
#include <string>

using namespace work_disk::tools::bot03;

static void verify_batch(
    IdentifierType type,
    std::size_t expected_length,
    int count
) {
    std::set<std::string> generated;

    for (int i = 0; i < count; ++i) {
        const std::string id =
            IdentifierGenerator::generate(type);

        assert(id.size() == expected_length);

        for (const unsigned char character : id) {
            assert(std::isalnum(character) != 0);
            assert(
                IdentifierAlphabet::value().find(
                    static_cast<char>(character)
                ) != std::string_view::npos
            );
        }

        generated.insert(id);
    }

    assert(generated.size() == static_cast<std::size_t>(count));

    std::cout
        << "TYPE_BATCH_UNIQUE="
        << generated.size()
        << '\n';
}

int main() {
    assert(IdentifierAlphabet::value().size() == 62);

    verify_batch(IdentifierType::Account, 9, 1000);
    verify_batch(IdentifierType::Entry, 11, 1000);
    verify_batch(IdentifierType::Fleet, 7, 1000);

    std::cout << "IDENTIFIER_SPACE_TEST=PASS\n";

    return 0;
}
