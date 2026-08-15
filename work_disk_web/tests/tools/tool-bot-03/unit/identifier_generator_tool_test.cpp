#include "identifier_generator_tool.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::bot03;

static void verify_identifier(
    IdentifierType type,
    std::size_t expected_length
) {
    const auto result =
        IdentifierGeneratorTool::generate(type);

    assert(result.hasValue());
    assert(result.error() == ToolBot03Error::None);
    assert(result.value().size() == expected_length);
}

int main() {
    verify_identifier(IdentifierType::Account, 9);
    verify_identifier(IdentifierType::Entry, 11);
    verify_identifier(IdentifierType::Fleet, 7);

    std::cout
        << "IDENTIFIER_GENERATOR_TOOL_TEST=PASS\n";

    return 0;
}
