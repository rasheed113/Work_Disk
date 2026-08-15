#pragma once

#include "tool_bot_03_error.h"

#include <string>

namespace work_disk::tools::bot03 {

class IdentifierGenerationResult {
public:
    static IdentifierGenerationResult success(std::string identifier);
    static IdentifierGenerationResult failure(ToolBot03Error error);

    bool hasValue() const noexcept;

    // Valid only when hasValue() == true.
    // Throws std::logic_error otherwise.
    const std::string& value() const;

    // Always safe to call.
    ToolBot03Error error() const noexcept;

private:
    IdentifierGenerationResult(
        std::string identifier,
        ToolBot03Error error
    );

    std::string identifier_;
    ToolBot03Error error_;
};

} // namespace work_disk::tools::bot03
