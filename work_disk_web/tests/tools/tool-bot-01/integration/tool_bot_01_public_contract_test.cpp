#include "tool_bot_01.h"

#include <cassert>
#include <iostream>
#include <string>

using namespace work_disk::tools::bot01;

int main() {
    const std::string account =
        IdentifierGeneratorTool::generate(IdentifierType::Account);

    const std::string entry =
        IdentifierGeneratorTool::generate(IdentifierType::Entry);

    const std::string fleet =
        IdentifierGeneratorTool::generate(IdentifierType::Fleet);

    assert(
        IdentifierValidatorTool::isValid(
            IdentifierType::Account,
            account
        )
    );

    assert(
        IdentifierValidatorTool::isValid(
            IdentifierType::Entry,
            entry
        )
    );

    assert(
        IdentifierValidatorTool::isValid(
            IdentifierType::Fleet,
            fleet
        )
    );

    std::cout << "ACCOUNT=" << account << '\n';
    std::cout << "ENTRY=" << entry << '\n';
    std::cout << "FLEET=" << fleet << '\n';
    std::cout << "TOOL_BOT_01_PUBLIC_CONTRACT_TEST=PASS\n";

    return 0;
}
