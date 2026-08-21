#pragma once

#include <cstdint>
#include <string>

namespace work_disk::tools::content_post {

enum class ContentKind : std::uint8_t {
    Post = 1,
};

enum class ContentResultCode : std::uint8_t {
    Created = 1,
    InvalidRequest,
    AuthorityRejected,
    ScopeRejected,
    Conflict,
    ExecutionFailed,
};

struct ContentCommand {
    std::string request_id;
    std::string authority_reference;
    std::string creation_scope_reference;
    ContentKind kind{ContentKind::Post};
    std::string payload_reference;
    std::string visibility_policy_reference;
    std::string idempotency_key;
};

struct ContentRef {
    std::string target_type;
    std::string target_id;
};

struct ContentResult {
    ContentResultCode code{ContentResultCode::InvalidRequest};
    ContentRef content{};
};

} // namespace work_disk::tools::content_post
