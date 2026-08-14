#include "credential_model.h"

#include <utility>

namespace work_disk::account {

Credential::Credential(
    std::string accountId,
    CredentialType type,
    std::string identifier
)
    : accountId_(std::move(accountId)),
      type_(type),
      identifier_(std::move(identifier)) {}

const std::string& Credential::accountId() const {
    return accountId_;
}

CredentialType Credential::type() const {
    return type_;
}

const std::string& Credential::identifier() const {
    return identifier_;
}

} // namespace work_disk::account
