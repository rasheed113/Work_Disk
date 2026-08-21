#pragma once

#include <string>

namespace work_disk::tools::bot05 {

enum class ApprovalDecision {
    Pending,
    Approved,
    Rejected
};

enum class ApprovalCreateStatus {
    Created,
    AlreadyExists,
    InvalidRequest,
    UnauthorisedCaller,
    StoreFailure,
    NotificationFailure
};

enum class ApprovalDecisionStatus {
    Approved,
    Rejected,
    IdempotentApproved,
    IdempotentRejected,
    UnknownRequest,
    InvalidDecision,
    UnauthenticatedDecision,
    ApproverMismatch,
    RequestContextMismatch,
    DecisionConflict,
    StoreFailure,
    DispatchFailure
};

enum class ApprovalQueryStatus {
    Pending,
    Approved,
    Rejected,
    UnknownRequest,
    StoreFailure
};

struct ApprovalRequest {
    std::string approvalRequestId;
    std::string callerId;
    std::string actionType;
    std::string targetType;
    std::string targetId;
    std::string approverId;
    std::string warningMessage;
    std::string decisionConsumerId;
    // Opaque caller-generated fingerprint of the exact approved action context.
    std::string actionFingerprint;
};

struct ApprovalDecisionInput {
    std::string approvalRequestId;
    std::string approverId;
    ApprovalDecision decision = ApprovalDecision::Pending;
    std::string authenticatedDecisionReference;
    // Must match the immutable request fingerprint.
    std::string actionFingerprint;
};

struct ApprovalState {
    ApprovalRequest request;
    ApprovalDecision decision = ApprovalDecision::Pending;
};

} // namespace work_disk::tools::bot05
