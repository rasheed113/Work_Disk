#include "relationship_tool.h"

namespace work_disk::tools::social_relationship {

namespace {
bool valid_operation(RelationshipOperation operation) {
    switch (operation) {
        case RelationshipOperation::Follow:
        case RelationshipOperation::Unfollow:
        case RelationshipOperation::RequestConnection:
        case RelationshipOperation::AcceptConnection:
        case RelationshipOperation::RejectConnection:
            return true;
    }
    return false;
}
}

bool RelationshipTool::valid(const RelationshipCommand& command) {
    return !command.request_id.empty()
        && !command.authority_reference.empty()
        && !command.relationship_scope_reference.empty()
        && !command.actor_reference.empty()
        && !command.subject_reference.empty()
        && command.actor_reference != command.subject_reference
        && valid_operation(command.operation)
        && !command.idempotency_key.empty()
        && !command.expected_version.empty();
}

RelationshipResult RelationshipTool::handle(const RelationshipCommand& command) const {
    if (!valid(command)) {
        return {RelationshipResultCode::InvalidRequest, {}};
    }
    if (!authority_.may_apply(command)) {
        return {RelationshipResultCode::AuthorityRejected, {}};
    }
    return provider_.apply(command);
}

} // namespace work_disk::tools::social_relationship
