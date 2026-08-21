#pragma once

#include <cstdint>
#include <string>

namespace work_disk::tools::media_attachment {

enum class MediaOperation : std::uint8_t { Attach = 1, Detach };
enum class MediaResultCode : std::uint8_t { Applied = 1, InvalidRequest, AuthorityRejected, ScopeRejected, Conflict, ExecutionFailed };

struct MediaCommand {
    std::string request_id;
    std::string authority_reference;
    std::string attachment_scope_reference;
    std::string owner_reference;
    std::string media_reference;
    MediaOperation operation{MediaOperation::Attach};
    std::string idempotency_key;
    std::string expected_version;
};

struct MediaResult {
    MediaResultCode code{MediaResultCode::InvalidRequest};
    std::string attachment_reference;
};

} // namespace work_disk::tools::media_attachment
