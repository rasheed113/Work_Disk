#pragma once

#include "delete_error.h"

#include <string>

namespace work_disk::tools::lifecycle::delete_tool {

enum class DeleteOutcome {
    Deleted,
    AlreadyDeleted,
    NotFound,
    PendingApproval,
    Rejected,
    Failed
};

class DeleteResult {
public:
    static DeleteResult deleted(std::string requestId);
    static DeleteResult alreadyDeleted(std::string requestId);
    static DeleteResult notFound(std::string requestId);
    static DeleteResult pendingApproval(std::string requestId);
    static DeleteResult rejected(std::string requestId);
    static DeleteResult invalidRequest(std::string requestId);
    static DeleteResult missingAuthority(std::string requestId);
    static DeleteResult invalidTarget(std::string requestId);
    static DeleteResult approvalFailure(std::string requestId);
    static DeleteResult pendingOperationFailure(std::string requestId);
    static DeleteResult pendingOperationConflict(std::string requestId);
    static DeleteResult persistenceFailure(std::string requestId);
    static DeleteResult transactionFailure(std::string requestId);
    static DeleteResult boundaryFailure(std::string requestId);

    DeleteOutcome outcome() const noexcept;
    bool succeeded() const noexcept;
    const std::string& requestId() const noexcept;
    DeleteError error() const noexcept;

private:
    DeleteResult(
        std::string requestId,
        DeleteOutcome outcome,
        DeleteError error
    );

    std::string requestId_;
    DeleteOutcome outcome_;
    DeleteError error_;
};

} // namespace work_disk::tools::lifecycle::delete_tool
