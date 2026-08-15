#include "tool_bot_03.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::bot03;

int main() {
    const auto invalid_type =
        static_cast<IdentifierType>(999);

    const auto result =
        IdentifierGeneratorTool::generate(invalid_type);

    assert(!result.hasValue());
    assert(
        result.error() ==
        ToolBot03Error::InvalidIdentifierType
    );

    const bool invalid_identifier_result =
        IdentifierValidatorTool::isValid(
            invalid_type,
            "anything"
        );

    assert(!invalid_identifier_result);

    std::cout
        << "PUBLIC_GENERATOR_INVALID_TYPE=PASS\n";

    std::cout
        << "PUBLIC_INVALID_TYPE_VALIDATION=PASS\n";

    std::cout
        << "TOOL_BOT_03_PUBLIC_FAILURE_CONTRACT_TEST=PASS\n";

    return 0;
}
