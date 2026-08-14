#pragma once

#include "tool_bot_01_error.h"

#include <string>

namespace work_disk::tools::bot01 {

class IdentifierGenerationResult {
public:
    static IdentifierGenerationResult success(std::string identifier);
    static IdentifierGenerationResult failure(ToolBot01Error error);

    bool hasValue() const noexcept;

    // Valid only when hasValue() == true.
    // Throws std::logic_error otherwise.
    const std::string& value() const;

    // Always safe to call.
    ToolBot01Error error() const noexcept;

private:
    IdentifierGenerationResult(
        std::string identifier,
        ToolBot01Error error
    );

    std::string identifier_;
    ToolBot01Error error_;
};

} // namespace work_disk::tools::bot01
