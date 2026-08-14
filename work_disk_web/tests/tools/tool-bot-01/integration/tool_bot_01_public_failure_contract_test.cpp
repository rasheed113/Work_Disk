#include "tool_bot_01.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::bot01;

int main() {
    const auto invalid_type =
        static_cast<IdentifierType>(999);

    const bool invalid_identifier_result =
        IdentifierValidatorTool::isValid(
            invalid_type,
            "anything"
        );

    assert(!invalid_identifier_result);

    std::cout
        << "PUBLIC_INVALID_TYPE_VALIDATION=PASS\n";

    std::cout
        << "TOOL_BOT_01_PUBLIC_FAILURE_CONTRACT_TEST=PASS\n";

    return 0;
}
