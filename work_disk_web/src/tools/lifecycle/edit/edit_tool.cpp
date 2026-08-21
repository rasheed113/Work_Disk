#include "edit_tool.h"

namespace work_disk::tools::edit {

bool EditTool::valid(const EditCommand& command) {
    return !command.request_id.empty()
        && !command.target_type.empty()
        && !command.target_id.empty()
        && !command.authority_reference.empty()
        && !command.edit_scope.empty()
        && command.expected_version > 0;
}

EditResult EditTool::handle(const EditCommand& command) const {
    if (!valid(command)) {
        return {EditResultCode::InvalidRequest, 0};
    }

    if (!authority_.authorised(command)) {
        return {EditResultCode::AuthorityRejected, 0};
    }

    const auto begin_result = store_.begin(command);
    switch (begin_result.code) {
        case EditResultCode::NoOp:
            return begin_result;
        case EditResultCode::NotFound:
        case EditResultCode::VersionConflict:
        case EditResultCode::LifecycleConflict:
        case EditResultCode::InvalidRequest:
        case EditResultCode::AuthorityRejected:
            return begin_result;
        default:
            break;
    }

    const auto execution_result = executor_.execute(command);
    if (execution_result.code == EditResultCode::ExecutionFailed ||
        execution_result.code == EditResultCode::VersionConflict ||
        execution_result.code == EditResultCode::LifecycleConflict ||
        execution_result.code == EditResultCode::NotFound ||
        execution_result.code == EditResultCode::AuthorityRejected) {
        return execution_result;
    }

    return store_.complete(command, execution_result);
}

} // namespace work_disk::tools::edit
