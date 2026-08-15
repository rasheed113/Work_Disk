#include "tool_bot_03_result.h"

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace work_disk::tools::bot03;

int main() {
    // 1. Successful result.
    const auto success =
        IdentifierGenerationResult::success("ABC123xyz");

    assert(success.hasValue());
    assert(success.error() == ToolBot03Error::None);
    assert(success.value() == "ABC123xyz");

    // 2. Empty successful value must be rejected.
    bool empty_success_threw = false;

    try {
        (void)IdentifierGenerationResult::success("");
    } catch (const std::invalid_argument&) {
        empty_success_threw = true;
    }

    assert(empty_success_threw);

    // 3. Failure result.
    const auto failure =
        IdentifierGenerationResult::failure(
            ToolBot03Error::InvalidIdentifierType
        );

    assert(!failure.hasValue());
    assert(
        failure.error() ==
        ToolBot03Error::InvalidIdentifierType
    );

    // 4. Failure must not expose a value.
    bool value_threw = false;

    try {
        (void)failure.value();
    } catch (const std::logic_error&) {
        value_threw = true;
    }

    assert(value_threw);

    // 5. failure(None) must be rejected.
    bool none_failure_threw = false;

    try {
        (void)IdentifierGenerationResult::failure(
            ToolBot03Error::None
        );
    } catch (const std::invalid_argument&) {
        none_failure_threw = true;
    }

    assert(none_failure_threw);

    std::cout << "RESULT_SUCCESS=PASS\n";
    std::cout << "RESULT_EMPTY_SUCCESS_GUARD=PASS\n";
    std::cout << "RESULT_FAILURE=PASS\n";
    std::cout << "RESULT_VALUE_GUARD=PASS\n";
    std::cout << "RESULT_NONE_FAILURE_GUARD=PASS\n";
    std::cout << "TOOL_BOT_03_RESULT_API_AUDIT=PASS\n";

    return 0;
}
