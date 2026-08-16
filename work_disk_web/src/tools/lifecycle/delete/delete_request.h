#pragma once

#include <string>

namespace work_disk::tools::lifecycle::delete_tool {

struct DeleteAuthority {
    std::string authorityReference;
    std::string approvalEvidence;
};

struct DeleteRequest {
    std::string requestId;
    std::string targetType;
    std::string targetId;

    DeleteAuthority authority;
};

} // namespace work_disk::tools::lifecycle::delete_tool
