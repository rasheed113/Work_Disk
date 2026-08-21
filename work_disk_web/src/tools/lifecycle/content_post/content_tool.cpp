#include "content_tool.h"

namespace work_disk::tools::content_post {

bool ContentTool::valid(const ContentCommand& command) {
    return !command.request_id.empty()
        && !command.authority_reference.empty()
        && !command.creation_scope_reference.empty()
        && command.kind == ContentKind::Post
        && !command.payload_reference.empty()
        && !command.visibility_policy_reference.empty()
        && !command.idempotency_key.empty();
}

ContentResult ContentTool::handle(const ContentCommand& command) const {
    if (!valid(command)) {
        return {ContentResultCode::InvalidRequest, {}};
    }

    if (!authority_.may_create(command)) {
        return {ContentResultCode::AuthorityRejected, {}};
    }

    return provider_.create(command);
}

} // namespace work_disk::tools::content_post
