#include "delete_tool.h"

namespace work_disk::tools::lifecycle::delete_tool {

DeleteTool::DeleteTool(
    DeleteExecutionBoundary& executionBoundary,
    DeletePendingOperationStore& pendingOperationStore,
    DeleteApprovalBoundary& approvalBoundary
) noexcept
    : executionBoundary_(executionBoundary),
      pendingOperationStore_(pendingOperationStore),
      approvalBoundary_(approvalBoundary) {}

DeleteResult DeleteTool::execute(
    const DeleteRequest& request
) const {
    if (request.requestId.empty() ||
        request.targetType.empty() ||
        request.targetId.empty()) {
        return DeleteResult::invalidRequest(request.requestId);
    }

    if (request.authority.authorityReference.empty()) {
        return DeleteResult::missingAuthority(request.requestId);
    }

    if (request.executionMode == DeleteExecutionMode::Immediate) {
        if (request.approvalDecision != DeleteApprovalDecision::None ||
            !request.authority.approvalEvidence.empty()) {
            return DeleteResult::invalidRequest(request.requestId);
        }

        return executeAuthorised(request);
    }

    if (request.executionMode != DeleteExecutionMode::ApprovalRequired) {
        return DeleteResult::invalidRequest(request.requestId);
    }

    if (request.approvalDecision == DeleteApprovalDecision::None) {
        const auto holdResult = pendingOperationStore_.hold(request);

        if (holdResult == PendingOperationOutcome::Failure) {
            return DeleteResult::pendingOperationFailure(request.requestId);
        }

        if (holdResult == PendingOperationOutcome::Conflict) {
            return DeleteResult::pendingOperationConflict(request.requestId);
        }

        if (holdResult == PendingOperationOutcome::AlreadyHeld) {
            return DeleteResult::pendingApproval(request.requestId);
        }

        const auto approvalResult =
            approvalBoundary_.requestApproval(request);

        if (approvalResult.failureCode != nullptr) {
            return DeleteResult::approvalFailure(request.requestId);
        }

        switch (approvalResult.decision) {
            case DeleteApprovalDecision::Pending:
                return DeleteResult::pendingApproval(request.requestId);

            case DeleteApprovalDecision::Approved: {
                if (approvalResult.approvalEvidence == nullptr ||
                    *approvalResult.approvalEvidence == '\0') {
                    return DeleteResult::approvalFailure(request.requestId);
                }

                DeleteRequest approvedRequest = request;
                approvedRequest.approvalDecision = DeleteApprovalDecision::Approved;
                approvedRequest.authority.approvalEvidence =
                    approvalResult.approvalEvidence;
                return executeApproved(approvedRequest);
            }

            case DeleteApprovalDecision::Rejected: {
                if (approvalResult.approvalEvidence == nullptr ||
                    *approvalResult.approvalEvidence == '\0') {
                    return DeleteResult::approvalFailure(request.requestId);
                }

                DeleteRequest rejectedRequest = request;
                rejectedRequest.approvalDecision = DeleteApprovalDecision::Rejected;
                rejectedRequest.authority.approvalEvidence =
                    approvalResult.approvalEvidence;
                return releaseRejected(rejectedRequest);
            }

            case DeleteApprovalDecision::None:
                return DeleteResult::approvalFailure(request.requestId);
        }
    }

    if (request.approvalDecision == DeleteApprovalDecision::Approved) {
        if (request.authority.approvalEvidence.empty()) {
            return DeleteResult::missingAuthority(request.requestId);
        }

        if (!pendingOperationStore_.isHeld(request.requestId) &&
            !pendingOperationStore_.isApproved(request.requestId)) {
            return DeleteResult::pendingOperationConflict(request.requestId);
        }

        return executeApproved(request);
    }

    if (request.approvalDecision == DeleteApprovalDecision::Rejected) {
        if (request.authority.approvalEvidence.empty()) {
            return DeleteResult::missingAuthority(request.requestId);
        }

        return releaseRejected(request);
    }

    if (request.approvalDecision == DeleteApprovalDecision::Pending) {
        return DeleteResult::pendingApproval(request.requestId);
    }

    return DeleteResult::invalidRequest(request.requestId);
}

DeleteResult DeleteTool::executeApproved(
    const DeleteRequest& request
) const {
    if (pendingOperationStore_.isHeld(request.requestId)) {
        const auto approvalResult = pendingOperationStore_.markApproved(
            request.requestId,
            request.authority.approvalEvidence
        );

        if (approvalResult == PendingOperationOutcome::Failure) {
            return DeleteResult::pendingOperationFailure(request.requestId);
        }

        if (approvalResult == PendingOperationOutcome::Conflict) {
            return DeleteResult::pendingOperationConflict(request.requestId);
        }
    } else if (!pendingOperationStore_.isApproved(request.requestId)) {
        return DeleteResult::pendingOperationConflict(request.requestId);
    }

    const auto result = executeAuthorised(request);

    if (result.outcome() == DeleteOutcome::Deleted ||
        result.outcome() == DeleteOutcome::AlreadyDeleted) {
        const auto completion =
            pendingOperationStore_.complete(request.requestId);

        if (completion == PendingOperationOutcome::Failure ||
            completion == PendingOperationOutcome::Conflict) {
            return DeleteResult::pendingOperationFailure(request.requestId);
        }
    }

    return result;
}

DeleteResult DeleteTool::releaseRejected(
    const DeleteRequest& request
) const {
    if (!pendingOperationStore_.isHeld(request.requestId)) {
        return DeleteResult::pendingOperationConflict(request.requestId);
    }

    const auto releaseResult =
        pendingOperationStore_.release(request.requestId);

    if (releaseResult == PendingOperationOutcome::Failure) {
        return DeleteResult::pendingOperationFailure(request.requestId);
    }

    if (releaseResult == PendingOperationOutcome::Conflict ||
        releaseResult == PendingOperationOutcome::Missing) {
        return DeleteResult::pendingOperationConflict(request.requestId);
    }

    return DeleteResult::rejected(request.requestId);
}

DeleteResult DeleteTool::executeAuthorised(
    const DeleteRequest& request
) const {
    const auto executionResult =
        executionBoundary_.execute(request);

    switch (executionResult.outcome()) {
        case DeleteExecutionOutcome::Deleted:
            return DeleteResult::deleted(request.requestId);

        case DeleteExecutionOutcome::AlreadyDeleted:
            return DeleteResult::alreadyDeleted(request.requestId);

        case DeleteExecutionOutcome::NotFound:
            return DeleteResult::notFound(request.requestId);

        case DeleteExecutionOutcome::ExecutionFailed:
            switch (executionResult.error()) {
                case DeleteExecutionError::PersistenceFailure:
                    return DeleteResult::persistenceFailure(request.requestId);

                case DeleteExecutionError::TransactionFailure:
                    return DeleteResult::transactionFailure(request.requestId);

                case DeleteExecutionError::BoundaryFailure:
                    return DeleteResult::boundaryFailure(request.requestId);

                case DeleteExecutionError::None:
                    return DeleteResult::boundaryFailure(request.requestId);
            }
    }

    return DeleteResult::boundaryFailure(request.requestId);
}

} // namespace work_disk::tools::lifecycle::delete_tool
