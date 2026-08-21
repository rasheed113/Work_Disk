#pragma once

#include "approval_request.h"

namespace work_disk::tools::bot05 {

struct WarningApprovalResult {
    ApprovalCreateStatus createStatus = ApprovalCreateStatus::InvalidRequest;
    ApprovalDecisionStatus decisionStatus = ApprovalDecisionStatus::InvalidDecision;
    ApprovalQueryStatus queryStatus = ApprovalQueryStatus::StoreFailure;
    ApprovalState state{};
};

} // namespace work_disk::tools::bot05
