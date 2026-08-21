#pragma once

#include <cstdint>
#include <string>

namespace work_disk::tools::social_relationship {

enum class RelationshipOperation : std::uint8_t {
    Follow = 1,
    Unfollow,
    RequestConnection,
    AcceptConnection,
    RejectConnection,
};

enum class RelationshipResultCode : std::uint8_t {
    Applied = 1,
    NoOp,
    InvalidRequest,
    AuthorityRejected,
    ScopeRejected,
    Conflict,
    ExecutionFailed,
};

struct RelationshipCommand {
    std::string request_id;
    std::string authority_reference;
    std::string relationship_scope_reference;
    std::string actor_reference;
    std::string subject_reference;
    RelationshipOperation operation{RelationshipOperation::Follow};
    std::string idempotency_key;
    std::string expected_version;
};

struct RelationshipResult {
    RelationshipResultCode code{RelationshipResultCode::InvalidRequest};
    std::string relationship_reference;
};

} // namespace work_disk::tools::social_relationship
