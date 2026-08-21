#include "media_tool.h"
namespace work_disk::tools::media_attachment {
namespace { bool valid_operation(MediaOperation op) { return op == MediaOperation::Attach || op == MediaOperation::Detach; } }
bool MediaTool::valid(const MediaCommand& c) {
    return !c.request_id.empty() && !c.authority_reference.empty() && !c.attachment_scope_reference.empty()
        && !c.owner_reference.empty() && !c.media_reference.empty() && valid_operation(c.operation)
        && !c.idempotency_key.empty() && !c.expected_version.empty();
}
MediaResult MediaTool::handle(const MediaCommand& c) const {
    if (!valid(c)) return {MediaResultCode::InvalidRequest, {}};
    if (!authority_.may_apply(c)) return {MediaResultCode::AuthorityRejected, {}};
    return provider_.apply(c);
}
} // namespace work_disk::tools::media_attachment
