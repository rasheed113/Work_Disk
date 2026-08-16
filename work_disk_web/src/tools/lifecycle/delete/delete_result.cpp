#include "delete_result.h"

#include <utility>

namespace work_disk::tools::lifecycle::delete_tool {

DeleteResult::DeleteResult(
    std::string requestId,
    DeleteOutcome outcome,
    DeleteError error
)
    : requestId_(std::move(requestId)),
      outcome_(outcome),
      error_(error) {}

DeleteResult DeleteResult::deleted(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::Deleted,
        DeleteError::None
    );
}

DeleteResult DeleteResult::alreadyDeleted(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::AlreadyDeleted,
        DeleteError::None
    );
}

DeleteResult DeleteResult::notFound(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::NotFound,
        DeleteError::None
    );
}

DeleteResult DeleteResult::invalidRequest(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::Failed,
        DeleteError::InvalidRequest
    );
}

DeleteResult DeleteResult::missingAuthority(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::Failed,
        DeleteError::MissingAuthority
    );
}

DeleteResult DeleteResult::invalidTarget(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::Failed,
        DeleteError::InvalidTarget
    );
}

DeleteResult DeleteResult::persistenceFailure(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::Failed,
        DeleteError::PersistenceFailure
    );
}

DeleteResult DeleteResult::transactionFailure(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::Failed,
        DeleteError::TransactionFailure
    );
}

DeleteResult DeleteResult::boundaryFailure(
    std::string requestId
) {
    return DeleteResult(
        std::move(requestId),
        DeleteOutcome::Failed,
        DeleteError::BoundaryFailure
    );
}

DeleteOutcome DeleteResult::outcome() const noexcept {
    return outcome_;
}

bool DeleteResult::succeeded() const noexcept {
    return outcome_ == DeleteOutcome::Deleted ||
           outcome_ == DeleteOutcome::AlreadyDeleted;
}

const std::string& DeleteResult::requestId() const noexcept {
    return requestId_;
}

DeleteError DeleteResult::error() const noexcept {
    return error_;
}

} // namespace work_disk::tools::lifecycle::delete_tool
