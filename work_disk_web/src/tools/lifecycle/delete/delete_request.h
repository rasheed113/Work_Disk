#pragma once

#include <string>

namespace work_disk::tools::lifecycle::delete_tool {

enum class DeleteExecutionMode {
    Immediate,
    ApprovalRequired
};

enum class DeleteApprovalDecision {
    None,
    Pending,
    Approved,
    Rejected
};

struct DeleteAuthority {
    std::string authorityReference;
    std::string approvalEvidence;
};

struct DeleteRequest {
    std::string requestId;
    std::string targetType;
    std::string targetId;

    DeleteExecutionMode executionMode = DeleteExecutionMode::Immediate;
    DeleteApprovalDecision approvalDecision = DeleteApprovalDecision::None;

    DeleteAuthority authority;
};

} // namespace work_disk::tools::lifecycle::delete_tool
