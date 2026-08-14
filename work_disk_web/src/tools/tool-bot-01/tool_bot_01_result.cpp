#include "tool_bot_01_result.h"

#include <stdexcept>
#include <utility>

namespace work_disk::tools::bot01 {

IdentifierGenerationResult::IdentifierGenerationResult(
    std::string identifier,
    ToolBot01Error error
)
    : identifier_(std::move(identifier)),
      error_(error) {
}

IdentifierGenerationResult IdentifierGenerationResult::success(
    std::string identifier
) {
    if (identifier.empty()) {
        throw std::invalid_argument(
            "Success result requires a non-empty identifier"
        );
    }

    return IdentifierGenerationResult(
        std::move(identifier),
        ToolBot01Error::None
    );
}

IdentifierGenerationResult IdentifierGenerationResult::failure(
    ToolBot01Error error
) {
    if (error == ToolBot01Error::None) {
        throw std::invalid_argument(
            "Failure result requires a non-None error"
        );
    }

    return IdentifierGenerationResult(
        {},
        error
    );
}

bool IdentifierGenerationResult::hasValue() const noexcept {
    return error_ == ToolBot01Error::None;
}

const std::string& IdentifierGenerationResult::value() const {
    if (!hasValue()) {
        throw std::logic_error(
            "Identifier generation result has no value"
        );
    }

    return identifier_;
}

ToolBot01Error IdentifierGenerationResult::error() const noexcept {
    return error_;
}

} // namespace work_disk::tools::bot01
