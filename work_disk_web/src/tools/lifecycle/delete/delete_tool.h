#pragma once

#include "delete_approval_boundary.h"
#include "delete_execution_boundary.h"
#include "delete_pending_operation.h"
#include "delete_request.h"
#include "delete_result.h"

namespace work_disk::tools::lifecycle::delete_tool {

class DeleteTool {
public:
    DeleteTool(
        DeleteExecutionBoundary& executionBoundary,
        DeletePendingOperationStore& pendingOperationStore,
        DeleteApprovalBoundary& approvalBoundary
    ) noexcept;

    DeleteResult execute(
        const DeleteRequest& request
    ) const;

private:
    DeleteResult executeApproved(
        const DeleteRequest& request
    ) const;

    DeleteResult releaseRejected(
        const DeleteRequest& request
    ) const;

    DeleteResult executeAuthorised(
        const DeleteRequest& request
    ) const;

    DeleteExecutionBoundary& executionBoundary_;
    DeletePendingOperationStore& pendingOperationStore_;
    DeleteApprovalBoundary& approvalBoundary_;
};

} // namespace work_disk::tools::lifecycle::delete_tool
