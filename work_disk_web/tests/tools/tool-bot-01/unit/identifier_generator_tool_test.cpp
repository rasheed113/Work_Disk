#include "identifier_generator_tool.h"

#include <cassert>
#include <cctype>
#include <iostream>
#include <string>

using namespace work_disk::tools::bot01;

static void verify_identifier(
    IdentifierType type,
    std::size_t expected_length
) {
    const std::string id =
        IdentifierGeneratorTool::generate(type);

    assert(id.size() == expected_length);

    for (const unsigned char character : id) {
        assert(std::isalnum(character) != 0);
    }
}

int main() {
    verify_identifier(IdentifierType::Account, 9);
    verify_identifier(IdentifierType::Entry, 11);
    verify_identifier(IdentifierType::Fleet, 7);

    std::cout << "IDENTIFIER_GENERATOR_TOOL_TEST=PASS\n";

    return 0;
}
