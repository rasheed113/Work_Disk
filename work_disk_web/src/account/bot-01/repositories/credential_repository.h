#ifndef WORK_DISK_CREDENTIAL_REPOSITORY_H
#define WORK_DISK_CREDENTIAL_REPOSITORY_H

#include "../models/credential_model.h"

#include <string>
#include <vector>

namespace work_disk::account {

class CredentialRepository {
public:
    bool save(const Credential& credential);

    bool exists(
        CredentialType type,
        const std::string& identifier
    ) const;

    Credential findByIdentifier(
        CredentialType type,
        const std::string& identifier
    ) const;

    std::vector<Credential> findByAccountId(
        const std::string& accountId
    ) const;

    bool remove(
        CredentialType type,
        const std::string& identifier
    );

private:
    std::vector<Credential> credentials_;
};

} // namespace work_disk::account

#endif
