#include "tool_bot_03_result.h"

#include <stdexcept>
#include <utility>

namespace work_disk::tools::bot03 {

IdentifierGenerationResult::IdentifierGenerationResult(
    std::string identifier,
    ToolBot03Error error
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
        ToolBot03Error::None
    );
}

IdentifierGenerationResult IdentifierGenerationResult::failure(
    ToolBot03Error error
) {
    if (error == ToolBot03Error::None) {
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
    return error_ == ToolBot03Error::None;
}

const std::string& IdentifierGenerationResult::value() const {
    if (!hasValue()) {
        throw std::logic_error(
            "Identifier generation result has no value"
        );
    }

    return identifier_;
}

ToolBot03Error IdentifierGenerationResult::error() const noexcept {
    return error_;
}

} // namespace work_disk::tools::bot03
