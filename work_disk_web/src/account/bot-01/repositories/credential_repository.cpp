#include "credential_repository.h"

namespace work_disk::account {

bool CredentialRepository::save(
    const Credential& credential
) {
    if (credential.accountId().empty() ||
        credential.identifier().empty()) {
        return false;
    }

    if (exists(
            credential.type(),
            credential.identifier())) {
        return false;
    }

    credentials_.push_back(credential);
    return true;
}

bool CredentialRepository::exists(
    CredentialType type,
    const std::string& identifier
) const {
    for (const auto& credential : credentials_) {
        if (credential.type() == type &&
            credential.identifier() == identifier) {
            return true;
        }
    }

    return false;
}

Credential CredentialRepository::findByIdentifier(
    CredentialType type,
    const std::string& identifier
) const {
    for (const auto& credential : credentials_) {
        if (credential.type() == type &&
            credential.identifier() == identifier) {
            return credential;
        }
    }

    return {};
}

std::vector<Credential> CredentialRepository::findByAccountId(
    const std::string& accountId
) const {
    std::vector<Credential> result;

    for (const auto& credential : credentials_) {
        if (credential.accountId() == accountId) {
            result.push_back(credential);
        }
    }

    return result;
}

bool CredentialRepository::remove(
    CredentialType type,
    const std::string& identifier
) {
    for (auto it = credentials_.begin();
         it != credentials_.end();
         ++it) {

        if (it->type() == type &&
            it->identifier() == identifier) {

            credentials_.erase(it);
            return true;
        }
    }

    return false;
}

} // namespace work_disk::account
