#include "delete_tool.h"

namespace work_disk::tools::lifecycle::delete_tool {

DeleteTool::DeleteTool(
    DeleteExecutionBoundary& executionBoundary
) noexcept
    : executionBoundary_(executionBoundary) {}

DeleteResult DeleteTool::execute(
    const DeleteRequest& request
) const {
    if (request.requestId.empty() ||
        request.targetType.empty() ||
        request.targetId.empty()) {
        return DeleteResult::invalidRequest(
            request.requestId
        );
    }

    if (request.authority.authorityReference.empty()) {
        return DeleteResult::missingAuthority(
            request.requestId
        );
    }

    const DeleteExecutionResult executionResult =
        executionBoundary_.execute(request);

    switch (executionResult.outcome()) {
        case DeleteExecutionOutcome::Deleted:
            return DeleteResult::deleted(
                request.requestId
            );

        case DeleteExecutionOutcome::AlreadyDeleted:
            return DeleteResult::alreadyDeleted(
                request.requestId
            );

        case DeleteExecutionOutcome::NotFound:
            return DeleteResult::notFound(
                request.requestId
            );

        case DeleteExecutionOutcome::ExecutionFailed:
            switch (executionResult.error()) {
                case DeleteExecutionError::PersistenceFailure:
                    return DeleteResult::persistenceFailure(
                        request.requestId
                    );

                case DeleteExecutionError::TransactionFailure:
                    return DeleteResult::transactionFailure(
                        request.requestId
                    );

                case DeleteExecutionError::BoundaryFailure:
                    return DeleteResult::boundaryFailure(
                        request.requestId
                    );

                case DeleteExecutionError::None:
                    return DeleteResult::boundaryFailure(
                        request.requestId
                    );
            }
    }

    return DeleteResult::boundaryFailure(
        request.requestId
    );
}

} // namespace work_disk::tools::lifecycle::delete_tool
