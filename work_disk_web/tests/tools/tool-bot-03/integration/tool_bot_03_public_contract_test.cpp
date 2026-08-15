#include "tool_bot_03.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::bot03;

static void verify_generation(
    IdentifierType type,
    std::size_t expected_length
) {
    const auto result =
        IdentifierGeneratorTool::generate(type);

    assert(result.hasValue());
    assert(result.error() == ToolBot03Error::None);
    assert(result.value().size() == expected_length);

    assert(
        IdentifierValidatorTool::isValid(
            type,
            result.value()
        )
    );
}

int main() {
    verify_generation(IdentifierType::Account, 9);
    verify_generation(IdentifierType::Entry, 11);
    verify_generation(IdentifierType::Fleet, 7);

    std::cout
        << "TOOL_BOT_03_PUBLIC_CONTRACT_TEST=PASS\n";

    return 0;
}
