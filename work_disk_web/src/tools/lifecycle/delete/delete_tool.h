#pragma once

#include "delete_execution_boundary.h"
#include "delete_request.h"
#include "delete_result.h"

namespace work_disk::tools::lifecycle::delete_tool {

class DeleteTool {
public:
    explicit DeleteTool(
        DeleteExecutionBoundary& executionBoundary
    ) noexcept;

    DeleteResult execute(
        const DeleteRequest& request
    ) const;

private:
    DeleteExecutionBoundary& executionBoundary_;
};

} // namespace work_disk::tools::lifecycle::delete_tool
