#include "identifier_validator_tool.h"

#include <cassert>
#include <iostream>

using namespace work_disk::tools::bot03;

int main() {
    assert(
        IdentifierValidatorTool::isValid(
            IdentifierType::Account,
            "324a6K8Xq"
        )
    );

    assert(
        IdentifierValidatorTool::isValid(
            IdentifierType::Entry,
            "A7k92Lm4QxZ"
        )
    );

    assert(
        IdentifierValidatorTool::isValid(
            IdentifierType::Fleet,
            "F7k2Lm9"
        )
    );

    assert(
        !IdentifierValidatorTool::isValid(
            IdentifierType::Account,
            "324a6K8$!"
        )
    );

    assert(
        !IdentifierValidatorTool::isValid(
            IdentifierType::Entry,
            "too-short"
        )
    );

    assert(
        !IdentifierValidatorTool::isValid(
            IdentifierType::Fleet,
            ""
        )
    );

    std::cout << "IDENTIFIER_VALIDATOR_TOOL_TEST=PASS\n";

    return 0;
}
